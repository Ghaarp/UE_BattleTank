// Fill out your copyright notice in the Description page of Project Settings.


#include "tankPlayerController.h"

void AtankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();
	if (Tank)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Tank->GetName());

	ControlledTank = GetControlledTank();
}

void AtankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimToCrosshair();
}

ATank* AtankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void AtankPlayerController::AimToCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
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
	GetWorld()->LineTraceSingleByChannel(OutHitResult, OutHitLocation, EndLocation, ECollisionChannel::ECC_Visibility, Params);
	if (OutHitResult.GetActor())
	{
		HitLocation = OutHitResult.Location;
		return true;
	}
	return false;
}