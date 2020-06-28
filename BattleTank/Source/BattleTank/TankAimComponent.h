// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

class UBarrelMeshComponent;
class UTurretMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();
	void SetBarrelMesh(UBarrelMeshComponent* BarrelToSet);
	void SetTurretMesh(UTurretMeshComponent* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector Location, float ProjectileSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	UBarrelMeshComponent* Barrel = nullptr;
	UTurretMeshComponent* Turret = nullptr;
	void GuideBarrelByDirection(FVector Direction);
	void RotateTurretByDirection(FVector Direction);
};
