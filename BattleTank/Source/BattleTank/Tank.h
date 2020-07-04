// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

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
		void InitAimComponent(UTankAimComponent* Component, UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitMovementComponent(UTankMovementComponent* Component, UTrackComponent* LeftTrack, UTrackComponent* RightTrack);

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovingComponent = nullptr;

};


