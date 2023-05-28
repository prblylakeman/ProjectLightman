// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMInteractComponent.h"
#include "PLMGameplayInterface.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UPLMInteractComponent::UPLMInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPLMInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPLMInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPLMInteractComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();



	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FVector End = EyeLocation + (EyeRotation.Vector() * 500);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	if (AActor* HitActor = Hit.GetActor())
	{
		if (HitActor->Implements<UPLMGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			IPLMGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.f, 0, 1.5f);

}