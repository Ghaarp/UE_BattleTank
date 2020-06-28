// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "BarrelMeshComponent.h"
#include "TankMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("AimComponent"));
	MovingComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovingComponent->ComponentTick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("Move"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(FName("Rotate"), this, &ATank::Rotate);
}

void ATank::Move(float AxisValue)
{
	MovingComponent->Move(AxisValue);
}

void ATank::Rotate(float AxisValue)
{
	MovingComponent->Rotate(AxisValue);
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

void ATank::SetLeftTrack(UTrackComponent* Track)
{
	MovingComponent->SetLeftTrack(Track);	
}

void ATank::SetRightTrack(UTrackComponent* Track)
{
	MovingComponent->SetRightTrack(Track);
}

void ATank::Fire()
{
	return;
	if (!LocalBarrel)
		return;

	UE_LOG(LogTemp, Warning, TEXT("BOOM!"));
	FVector StartLoc = LocalBarrel->GetSocketLocation(FName("FiringSocket"));
	FActorSpawnParameters Params = FActorSpawnParameters();
	//GetWorld()->SpawnActor<AProjectile>(Projectile, StartLoc, Params);
	AProjectile* ProjectileObj = GetWorld()->SpawnActor<AProjectile>(Projectile,
		LocalBarrel->GetSocketLocation(FName("FiringSocket")),
		LocalBarrel->GetSocketRotation(FName("FiringSocket")));

	ProjectileObj->Launch(ProjectileStartingSpeed);
}


