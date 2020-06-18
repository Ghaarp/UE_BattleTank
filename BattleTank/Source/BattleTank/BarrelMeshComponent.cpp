// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "BarrelMeshComponent.h"

void UBarrelMeshComponent::Elevate(float ElevationSpeed)
{
	ElevationSpeed = FMath::Clamp(ElevationSpeed, -1.f, 1.f);
	float Change = ElevationSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float NewAngle = GetRelativeRotation().Pitch + Change;

	NewAngle = FMath::Clamp(NewAngle, LowerAngle, UpperAngle);
	SetRelativeRotation(FRotator(NewAngle, 0, 0));
}