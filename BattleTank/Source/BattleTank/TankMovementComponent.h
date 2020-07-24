// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class UTrackComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UTankMovementComponent();
	virtual void BeginPlay() override;
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	void SetLeftTrack(UTrackComponent* Track);
	void SetRightTrack(UTrackComponent* Track);

	void TurnOffEngine();

	void Move(float AxisValue);
	void Rotate(float AxisValue);

private:
	UTrackComponent* LeftTrack = nullptr;
	UTrackComponent* RightTrack = nullptr;

	void ApplyForceToTank();

	float LeftThrottle = 0;
	float RightThrottle = 0;

	bool bEngineTurnedOn = true;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
