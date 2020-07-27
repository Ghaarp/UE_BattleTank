// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTrackComponent;
class UTankMovementComponent;
class UParticleSystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void Move(float AxisValue);
	void Rotate(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitAimComponent(UTankAimComponent* Component, UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitMovementComponent(UTankMovementComponent* Component, UTrackComponent* LeftTrack, UTrackComponent* RightTrack);

	UFUNCTION(BlueprintPure, Category = Setup)
	float GetHealthPerc() const;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; 

	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* ParticlesExplosion = nullptr;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetParticles(UParticleSystemComponent* incParticlesExplosion);

	FTankDelegate OnDeath;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankAimComponent* AimComponent = nullptr;

	float StartingHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float Health = StartingHealth;


	bool bIsTankdestroyed = false;

private:
	void DestroyThisTank();

};


