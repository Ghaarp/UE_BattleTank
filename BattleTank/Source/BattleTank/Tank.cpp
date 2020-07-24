// Fill out your copyright notice in the Description page of Project Settings.
#include "BarrelMeshComponent.h"
#include "TankMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "TankAimComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsTankdestroyed && Health <= 0.f)
	{
		DestroyThisTank();
		Health = 0.f;
		bIsTankdestroyed = true;
	}	
}

void ATank::DestroyThisTank()
{
	MovingComponent->TurnOffEngine();
	if(AimComponent)
		AimComponent->Deactivate();
	
	if(ParticlesExplosion)
	ParticlesExplosion->Activate();
}

void ATank::SetParticles(UParticleSystemComponent* incParticlesExplosion)
{
	ParticlesExplosion = incParticlesExplosion;
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
	if (!ensure(MovingComponent)) return;
	MovingComponent->Move(AxisValue);
}

void ATank::Rotate(float AxisValue)
{
	if (!ensure(MovingComponent)) return;
	MovingComponent->Rotate(AxisValue);
}

void ATank::InitAimComponent(UTankAimComponent* Component, UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet)
{
	AimComponent = Component;
	AimComponent->SetBarrelMesh(BarrelToSet);
	AimComponent->SetTurretMesh(TurretToSet);
}

void ATank::InitMovementComponent(UTankMovementComponent* Component, UTrackComponent* LeftTrack, UTrackComponent* RightTrack)
{
	MovingComponent = Component;
	MovingComponent->SetLeftTrack(LeftTrack);
	MovingComponent->SetRightTrack(RightTrack);
}

float ATank::GetHealth()
{
	return Health;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	return DamageAmount;
}



