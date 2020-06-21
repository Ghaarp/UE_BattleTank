// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyProjectileMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UMyProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	UMyProjectileMovementComponent();
};
