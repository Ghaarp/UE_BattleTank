// Fill out your copyright notice in the Description page of Project Settings.
#include "tankPlayerController.h"
#include "TankAimComponent.h"

void AtankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();

	ControlledTank = GetControlledTank();

	AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	if (AimComponent)
	{
		OnCreateAimingComponent(AimComponent);
	}	
}


void AtankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto Tank = Cast<ATank>(InPawn);
		if (!ensure(Tank))
			return;

		Tank->OnDeath.AddUniqueDynamic(this, &AtankPlayerController::OnTankDeath);
	}
}

void AtankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimToCrosshair();
}

void AtankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

ATank* AtankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void AtankPlayerController::AimToCrosshair()
{
	if (!ensure(AimComponent))
		return;
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimComponent->AimAt(HitLocation);
	}
}

bool AtankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector WorldDirection, OutHitLocation;
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	FVector2D Vector(ViewportX * CrosshairXPos, ViewportY * CrosshairYPos);

	DeprojectScreenPositionToWorld(Vector.X, Vector.Y, OutHitLocation, WorldDirection);
	FVector EndLocation = OutHitLocation + WorldDirection * 50000;

	FHitResult OutHitResult;

	FCollisionQueryParams Params(NAME_None, true, GetPawn());
	GetWorld()->LineTraceSingleByChannel(OutHitResult, OutHitLocation, EndLocation, ECollisionChannel::ECC_Camera, Params);
	if (OutHitResult.GetActor())
	{
		HitLocation = OutHitResult.Location;
		return true;
	}
	return false;
}
