// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();
	if(PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *PlayerTank->GetName());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FiringEnabled)
	{
		CurrentFireDelay += DeltaTime;
	}

	if (CurrentFireDelay > FiringDelay)
	{
		FiringEnabled = true;
		CurrentFireDelay = 0;
	}
		

	if (ControlledTank && PlayerTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorTransform().GetLocation());
		if (FiringEnabled)
		{
			ControlledTank->Fire();
			FiringEnabled = false;
		}
	}
		
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	AtankPlayerController* TankPlayerController = Cast<AtankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (TankPlayerController)
		return Cast<ATank>(TankPlayerController->GetPawn());

	return nullptr;
}