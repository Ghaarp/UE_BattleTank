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
	UTrackComponent();
	UPROPERTY(EditDefaultsOnly)
		float MaxForce = 40000000.f;

	void ApplyForce();
	void SetThrottle(float ThrottleValue);
	void AddSideFriction();

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float Throttle = 0.f;
};
