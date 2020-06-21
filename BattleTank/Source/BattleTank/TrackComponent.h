// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
		float MaxForce = 400000.f;

	void ApplyForce(float Throttle);
};
