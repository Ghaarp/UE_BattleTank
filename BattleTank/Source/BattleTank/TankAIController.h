// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "tankPlayerController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; 

	UPROPERTY(EditDefaultsOnly)
		float FiringDelay = 3;

	

private:
	ATank *PlayerTank, *ControlledTank;
	ATank* GetPlayerTank();

	bool FiringEnabled = true;
	float CurrentFireDelay = 0;
};


