// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();
	PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
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

	if (ControlledTank && PlayerTank && bControlNeeded)
	{
		UTankAimComponent* AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
		if(!ensure(AimComponent))
			return;

		AimComponent->AimAt(PlayerTank->GetActorTransform().GetLocation());
		EAimState ActualState = AimComponent->GetAimState();
		if (FiringEnabled && ActualState == EAimState::Ready)
		{
			AimComponent->Fire();
			FiringEnabled = false;
		}

		MoveToActor(PlayerTank, 1000.f, true, true, false);
	}
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto Tank = Cast<ATank>(InPawn);
		if (!ensure(Tank))
			return;

		Tank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	bControlNeeded = false;
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