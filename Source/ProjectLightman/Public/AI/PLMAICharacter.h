// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PLMAICharacter.generated.h"

class UPawnSensingComponent;
class UPLMAttributeComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APLMAICharacter();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UPLMAttributeComponent* AttributeComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnChangeInitiated(AActor* InstigatorActor, UPLMAttributeComponent* OwningComponent, int NewHealth, int Delta);

	void SetTargetActor(AActor* NewTarget);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
