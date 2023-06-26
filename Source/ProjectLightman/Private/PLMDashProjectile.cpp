// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APLMDashProjectile::APLMDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	ProjectileMovementComponent->InitialSpeed = 6000;
}

void APLMDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &APLMDashProjectile::Explode, DetonateDelay);
}

void APLMDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());

	ParticleSystemComponent->DeactivateSystem();

	ProjectileMovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &APLMDashProjectile::TeleportInstigator, TeleportDelay);
}

void APLMDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}
