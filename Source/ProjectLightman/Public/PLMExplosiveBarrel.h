// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLMExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APLMExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere);
	URadialForceComponent* RadialForceComponent;


	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
