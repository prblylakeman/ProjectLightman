// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMProjectileBase.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PLMAttributeComponent.h"

// Sets default values
APLMProjectileBase::APLMProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentHit.AddDynamic(this, &APLMProjectileBase::OnActorHit);
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 8000;
}


// Called when the game starts or when spawned
void APLMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APLMProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UPLMAttributeComponent* AttributeComponent = Cast<UPLMAttributeComponent>(OtherActor->GetComponentByClass(UPLMAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-20);

			Explode();
		}
	}

	Explode();
}

void APLMProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());

		Destroy();

	}
}


// Called every frame
void APLMProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

