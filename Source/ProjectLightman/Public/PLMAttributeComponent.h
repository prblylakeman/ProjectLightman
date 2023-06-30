// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PLMAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnChangeInitiated, AActor*, InstigatorActor, UPLMAttributeComponent*, OwningComponent, int, NewHealth, int, Delta);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	// BlueprintReadOnly - read-only in the Blueprint scripting (does not affect details panel)
	// BlueprintReadWrite - read-write access in Blueprints

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes");
	int Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes");
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes");
	int InterpolatedHealth;

	// HealthMax, Stamina, Strength, Mana, Energy, CriticalHitChance, BaseDamage, CriticalHitDamage, 

	// Called when the game starts

public:	

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnChangeInitiated OnChangeInitiated;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(int Delta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
