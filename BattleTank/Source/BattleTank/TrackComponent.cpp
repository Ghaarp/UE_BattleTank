// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackComponent.h"

UTrackComponent::UTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTrackComponent::OnHit);
}

void UTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
	ApplyForce();
	AddSideFriction();
}

void UTrackComponent::SetThrottle(float ThrottleValue)
{
	Throttle = ThrottleValue;	
}

void UTrackComponent::ApplyForce()
{ 
	auto Vector = GetForwardVector() * MaxForce * Throttle;
	auto Location = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Vector, Location);
	
	Throttle = 0.f;
}

void UTrackComponent::AddSideFriction()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Multiplier = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -Multiplier / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 4;
	TankRoot->AddForce(CorrectionForce);
}
