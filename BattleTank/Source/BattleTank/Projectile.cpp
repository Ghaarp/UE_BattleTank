// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UMyProjectileMovementComponent>(FName("ProjectileMovement"));

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particles"));
	Particles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ParticlesExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticlesExplosion"));
	ParticlesExplosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticlesExplosion->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	RadialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RadialForce->ImpulseStrength = 100000000.f;
	RadialForce->Radius = 800.f;
	RadialForce->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Particles->Deactivate();
	ParticlesExplosion->Activate();
	RadialForce->FireImpulse();	
	UGameplayStatics::ApplyRadialDamageWithFalloff(this, Damage, 1, GetActorLocation(), 10.f, RadialForce->Radius + 100.f, 1.5f, UDamageType::StaticClass(), TArray<AActor*>());
	CollisionMesh->DestroyComponent();
	FTimerHandle Timer = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpired, DestroyTimer, false);
}

void AProjectile::OnTimerExpired()
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float Speed)
{
	if (!ensure(ProjectileMovement))
		return;

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

