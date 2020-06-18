// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "tankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AtankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	void AimToCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXPos = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYPos = 0.5;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ATank* ControlledTank;
};