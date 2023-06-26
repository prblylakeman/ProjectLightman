// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMTargetDummy.h"
#include "PLMAttributeComponent.h"

// Sets default values
APLMTargetDummy::APLMTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	AttributeComponent = CreateDefaultSubobject<UPLMAttributeComponent>("AttributeComponent");
	AttributeComponent->OnChangeInitiated.AddDynamic(this, &APLMTargetDummy::OnChangeInitiated);

}

// Called when the game starts or when spawned
void APLMTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void APLMTargetDummy::OnChangeInitiated(AActor* InstigatorActor, UPLMAttributeComponent* OwningComponent, int NewHealth, int Delta)
{
	if (Delta < 0)
	{
		StaticMeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	
}

// Called every frame
void APLMTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

