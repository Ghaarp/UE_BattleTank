// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackComponent.h"

void UTrackComponent::ApplyForce(float Throttle)
{
	auto Vector = GetForwardVector() * MaxForce * Throttle;
	auto Location = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Vector, Location);
}
