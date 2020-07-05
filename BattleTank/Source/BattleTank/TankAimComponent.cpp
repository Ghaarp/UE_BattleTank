// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelMeshComponent.h"
#include "TurretMeshComponent.h"
#include "Projectile.h"
#include "TankAimComponent.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimComponent::AimAt(FVector Location)
{
	FString Name = GetName();
	if (!ensure(Barrel))
	{
		return;		
	}

	FVector BarrelLoc = Barrel->GetSocketLocation(FName("FiringSocket"));
	FVector Result;
	if (!UGameplayStatics::SuggestProjectileVelocity(
		this,
		Result,
		BarrelLoc,
		Location,
		ProjectileStartingSpeed,
		false,
		1.f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>()))
	{
		return;
	}

	FVector DirectionUnitVector = Result.GetSafeNormal();
	RotateTurretByDirection(DirectionUnitVector);
	GuideBarrelByDirection(DirectionUnitVector);
}


// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimComponent::RotateTurretByDirection(FVector Direction)
{
	FRotator Rotator = Direction.Rotation();
	Turret->RotateToDirection(Rotator.Yaw);
}

void UTankAimComponent::GuideBarrelByDirection(FVector Direction)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator Rotator = Direction.Rotation();
	FRotator Delta = Rotator - BarrelRotator;
	Barrel->Elevate(Delta.Pitch);
}


void UTankAimComponent::SetBarrelMesh(UBarrelMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimComponent::SetTurretMesh(UTurretMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}

// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UTankAimComponent::Fire()
{
	if (!ensure(Barrel))
		return;

	FVector StartLoc = Barrel->GetSocketLocation(FName("FiringSocket"));
	FActorSpawnParameters Params = FActorSpawnParameters();
	//GetWorld()->SpawnActor<AProjectile>(Projectile, StartLoc, Params);
	AProjectile* ProjectileObj = GetWorld()->SpawnActor<AProjectile>(Projectile,
		Barrel->GetSocketLocation(FName("FiringSocket")),
		Barrel->GetSocketRotation(FName("FiringSocket")));

	ProjectileObj->Launch(ProjectileStartingSpeed);
}

