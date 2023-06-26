// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLMTargetDummy.generated.h"

class UPLMAttributeComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APLMTargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UPLMAttributeComponent* AttributeComponent;

	UFUNCTION()
	void OnChangeInitiated(AActor* InstigatorActor, UPLMAttributeComponent* OwningComponent, int NewHealth, int Delta);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
