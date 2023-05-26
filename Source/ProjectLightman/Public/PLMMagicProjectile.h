// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLMMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APLMMagicProjectile();

protected:

	UPROPERTY(VisibleAnywhere);
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere);
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* EffectComponent;

	UPROPERTY(VisibleAnywhere);
	UNiagaraComponent* NiagaraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
