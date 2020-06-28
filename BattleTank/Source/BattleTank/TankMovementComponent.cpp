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
	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector MoveVelocityUnit = MoveVelocity.GetSafeNormal();
	float Multiplier = FVector::DotProduct(TankForward, MoveVelocityUnit);
	Move(Multiplier);
}

void UTankMovementComponent::SetLeftTrack(UTrackComponent* Track)
{
	LeftTrack = Track;
}

void UTankMovementComponent::SetRightTrack(UTrackComponent* Track)
{
	RightTrack = Track;
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

void UTankMovementComponent::ComponentTick(float DeltaTime)
{
	ApplyForceToTank();
}

void UTankMovementComponent::ApplyForceToTank()
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftThrottle = FMath::Clamp<float>(LeftThrottle, -1.f, 1.f);
	RightThrottle = FMath::Clamp<float>(RightThrottle, -1.f, 1.f);

	if (LeftThrottle == 0 && RightThrottle == 0)
		return;

	LeftTrack->ApplyForce(LeftThrottle);
	RightTrack->ApplyForce(RightThrottle);

	LeftThrottle = 0.f;
	RightThrottle = 0.f;
}
