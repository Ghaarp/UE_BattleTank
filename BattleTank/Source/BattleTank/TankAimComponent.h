// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EAimState : uint8
{
	Reloading,
	Aiming,
	Ready
};

class UBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();

	UPROPERTY(BlueprintReadOnly)
	EAimState AimState = EAimState::Reloading;

	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileStartingSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> Projectile;

	void SetBarrelMesh(UBarrelMeshComponent* BarrelToSet);
	void SetTurretMesh(UTurretMeshComponent* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	UBarrelMeshComponent* Barrel = nullptr;
	UTurretMeshComponent* Turret = nullptr;
	void GuideBarrelByDirection(FVector Direction);
	void RotateTurretByDirection(FVector Direction);
};
