// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PLMAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIGHTMAN_API UPLMAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPLMAttributeComponent();

protected:

	// EditAnywhere - edit in BP editor and per-instance in level
	// VisibleAnywhere - 'read-only' in editor and level (use for components)
	// EditDefaultsOnly - hide variable per-instance, edit in BP editor only
	// VisibleDefaultsOnly - 'read-only' access for variable, only in BP editor (uncommon)
	// EditInstanceOnly - allow only editing of instance (placed in level)
	// BlueprintReadOnly - read-only in the Blueprint scriptiong (does not affect details panel)
	// BlueprintReadWrite - read-write access in Blueprints

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes");
	float Health;

	// HealthMax, Stamina, Strength, Mana, Energy, CriticalHitChance, BaseDamage, CriticalHitDamage, 

	// Called when the game starts

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);
		
};
