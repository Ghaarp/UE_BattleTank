// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectile;
class UTrackComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void Move(float AxisValue);
	void Rotate(float AxisValue);

	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelMesh(UBarrelMeshComponent* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretMesh(UTurretMeshComponent* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetLeftTrack(UTrackComponent* Track);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRightTrack(UTrackComponent* Track);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileStartingSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> Projectile;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UTankAimComponent* AimComponent;
	UTankMovementComponent* MovingComponent;

private:
	UBarrelMeshComponent* LocalBarrel = nullptr;
};

