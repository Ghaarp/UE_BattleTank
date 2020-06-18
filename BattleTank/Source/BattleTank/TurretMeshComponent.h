// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTurretMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateToDirection(float Angle);

	UPROPERTY(EditAnywhere)
		float Speed = 40.f;

private:
	float SetInBorders(float Value);
};
