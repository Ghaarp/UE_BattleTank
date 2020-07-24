// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EAimState : uint8
{
	NoAmmo, 
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

	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileStartingSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, Category = Firing)
		float ReloadTime = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
		uint8 Ammo = 20;

	void SetBarrelMesh(UBarrelMeshComponent* BarrelToSet);
	void SetTurretMesh(UTurretMeshComponent* TurretToSet);

	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	FString GetAmmo();

	EAimState GetAimState() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetProjectileClass(TSubclassOf<AProjectile> IncProjectile);

	void Deactivate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
	UPROPERTY(BlueprintReadOnly)
		EAimState AimState = EAimState::Reloading;

private:
	UBarrelMeshComponent* Barrel = nullptr;
	UTurretMeshComponent* Turret = nullptr;
	float LastShootTime = 0.f;

	void GuideBarrelByDirection(FVector Direction);
	void RotateTurretByDirection(FVector Direction);
	bool IsBarrelMoving();
	FVector DirectionUnitVector = FVector(0.f, 0.f, 0.f);

	bool bIsAimingEnabled = true;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
