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
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	
	RadialForceComponent->SetAutoActivate(false);

	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->ImpulseStrength = 2500.f;
	RadialForceComponent->bImpulseVelChange = true;

	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);

}



void APLMExplosiveBarrel::PostInitializeComponents()
{
	// call parent
	Super::PostInitializeComponents();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &APLMExplosiveBarrel::OnActorHit);
}

void APLMExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
	Destroy();
}
