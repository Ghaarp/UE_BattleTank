// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "DrawDebugHelpers.h"
#include "TrackComponent.h"
#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveVelocityUnit = MoveVelocity.GetSafeNormal();
	float MovingMultiplier = FVector::DotProduct(TankForward, MoveVelocityUnit);
	Move(MovingMultiplier);

	float RotationMultiplier = FVector::CrossProduct(TankForward, MoveVelocityUnit).Z;
	Rotate(RotationMultiplier * -1);
}

void UTankMovementComponent::SetLeftTrack(UTrackComponent* Track)
{
	LeftTrack = Track;
}

void UTankMovementComponent::SetRightTrack(UTrackComponent* Track)
{
	RightTrack = Track;
}

void UTankMovementComponent::TurnOffEngine()
{
	bEngineTurnedOn = false;
}

void UTankMovementComponent::Move(float AxisValue)
{
	LeftThrottle += AxisValue;
	RightThrottle += AxisValue;
}

void UTankMovementComponent::Rotate(float AxisValue)
{
	LeftThrottle -= AxisValue;
	RightThrottle += AxisValue;
}

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!bEngineTurnedOn) return;
	ApplyForceToTank();
}

void UTankMovementComponent::ApplyForceToTank()
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	LeftThrottle = FMath::Clamp<float>(LeftThrottle, -1.f, 1.f);
	RightThrottle = FMath::Clamp<float>(RightThrottle, -1.f, 1.f);

	if (LeftThrottle == 0 && RightThrottle == 0)
		return;

	LeftTrack->SetThrottle(LeftThrottle);
	RightTrack->SetThrottle(RightThrottle);

	LeftThrottle = 0.f;
	RightThrottle = 0.f;
}
