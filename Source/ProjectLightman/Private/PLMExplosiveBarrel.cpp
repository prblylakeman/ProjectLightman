// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APLMExplosiveBarrel::APLMExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	//StaticMeshComponent->OnComponentHit.AddDynamic(this, &APLMExplosiveBarrel::OnActorHit);
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");

}

// Called when the game starts or when spawned
void APLMExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLMExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

