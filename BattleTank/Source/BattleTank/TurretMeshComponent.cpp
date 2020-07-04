// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "TurretMeshComponent.h"

void UTurretMeshComponent::RotateToDirection(float Angle)
{
	AActor* Owner = GetOwner();
	FRotator Rotator = Owner->GetTransform().Rotator();
	float RootYaw = Rotator.Yaw;
	float CalculatedAngle = Angle;
	float CurrentAngle = SetInBorders(GetRelativeRotation().Yaw + RootYaw);
	
	float Difference = Angle - CurrentAngle;
	float DifferenceAbs = UKismetMathLibrary::Abs(Difference);
	bool Reverse = UKismetMathLibrary::Abs(Difference) > 180;
	float ChangePerTick = Speed * GetWorld()->DeltaTimeSeconds;
	if (DifferenceAbs > ChangePerTick)	
	{
		if (Reverse)
		{
			CalculatedAngle = CurrentAngle - ChangePerTick * UKismetMathLibrary::SignOfFloat(Difference);
		}
		else
		{
			CalculatedAngle = CurrentAngle + ChangePerTick * UKismetMathLibrary::SignOfFloat(Difference);
		}		
	}
	SetRelativeRotation(FRotator(0, CalculatedAngle - RootYaw, 0));
}

float UTurretMeshComponent::SetInBorders(float Value)
{
	while (Value > 180)
		Value -= 360;

	while (Value < -180)
		Value += 360;

	return Value;
}