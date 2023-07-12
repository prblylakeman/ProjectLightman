// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMProjectileBase.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PLMAttributeComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
APLMProjectileBase::APLMProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentHit.AddDynamic(this, &APLMProjectileBase::OnActorHit);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APLMProjectileBase::OnActorOverlap);
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 8000;

	LoopingAudioComponent = CreateDefaultSubobject<UAudioComponent>("LoopingAudioComponent");
	LoopingAudioComponent->SetupAttachment(RootComponent);

	ImpactShakeInnerRadius = 100.0f;
	ImpactShakeOuterRadius = 1000.0f;

	Damage = -20;

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
			AttributeComponent->ApplyHealthChange(Damage);

			Explode();
		}
	}

	Explode();
}

void APLMProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UPLMAttributeComponent* AttributeComponent = Cast<UPLMAttributeComponent>(OtherActor->GetComponentByClass(UPLMAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(Damage);

			Explode();
		}
	}
}


void APLMProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());

		UGameplayStatics::PlaySoundAtLocation(this, ImpactAudio, GetActorLocation(), GetActorRotation());

		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);

		Destroy();

	}
}


// Called every frame
void APLMProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

