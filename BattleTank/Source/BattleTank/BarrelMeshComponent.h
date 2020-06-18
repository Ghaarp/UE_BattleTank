// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrelMeshComponent.generated.h"
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UBarrelMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Elevate(float ElevationSpeed);

    UPROPERTY(EditAnywhere)
        float MaxDegreesPerSec = 10;
        
    UPROPERTY(EditAnywhere)
        float UpperAngle = 20;

    UPROPERTY(EditAnywhere)
        float LowerAngle = -6;
};
