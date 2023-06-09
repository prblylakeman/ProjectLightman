// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMAttributeComponent.h"

// Sets default values for this component's properties
UPLMAttributeComponent::UPLMAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	Health = 100;
	InterpolatedHealth = 100;
	DamageOverTime = false;
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

bool UPLMAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, int Delta)
{
	//Health += Delta;

	int OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0, MaxHealth);

	int ActualDelta = Health - OldHealth;
	OnChangeInitiated.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

void UPLMAttributeComponent::DamagingOverTime()
{
	if (DamageOverTime)
	{
		//
	}
}

UPLMAttributeComponent* UPLMAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UPLMAttributeComponent>();
	}

	return nullptr;

}

bool UPLMAttributeComponent::IsActorAlive(AActor* Actor)
{
	UPLMAttributeComponent* AttributeComponent = GetAttributes(Actor);
	if (AttributeComponent)
	{
		return AttributeComponent->IsAlive();
	}

	return false;
}


