// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMAttributeComponent.h"

// Sets default values for this component's properties
UPLMAttributeComponent::UPLMAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	Health = 100;
	InterpolatedHealth = 100;
}

// Called when the game starts
void UPLMAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UPLMAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPLMAttributeComponent::IsAlive() const
{
	return Health > 0;
}

bool UPLMAttributeComponent::ApplyHealthChange(int Delta)
{
	Health += Delta;

	OnChangeInitiated.Broadcast(nullptr, this, Health, Delta);

	return true;
}



