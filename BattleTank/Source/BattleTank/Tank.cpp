// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "BarrelMeshComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("AimComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector Location)
{
	AimComponent->AimAt(Location, ProjectileStartingSpeed);
}

void ATank::SetBarrelMesh(UBarrelMeshComponent* BarrelToSet)
{
	AimComponent->SetBarrelMesh(BarrelToSet);
	LocalBarrel = BarrelToSet;
}

void ATank::SetTurretMesh(UTurretMeshComponent* TurretToSet)
{
	AimComponent->SetTurretMesh(TurretToSet);
}

void ATank::Fire()
{

	if (!LocalBarrel)
		return;

	UE_LOG(LogTemp, Warning, TEXT("BOOM!"));
	FVector StartLoc = LocalBarrel->GetSocketLocation(FName("FiringSocket"));
	FActorSpawnParameters Params = FActorSpawnParameters();
	//GetWorld()->SpawnActor<AProjectile>(Projectile, StartLoc, Params);
	GetWorld()->SpawnActor<AProjectile>(Projectile,
		LocalBarrel->GetSocketLocation(FName("FiringSocket")),
		LocalBarrel->GetSocketRotation(FName("FiringSocket")));
}


