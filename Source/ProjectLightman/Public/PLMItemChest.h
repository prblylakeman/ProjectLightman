// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLMGameplayInterface.h"
#include "PLMItemChest.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UParticleSystemComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMItemChest : public AActor, public IPLMGameplayInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere);
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	APLMItemChest();

protected:

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* GoldMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UParticleSystemComponent* ParticleSystemComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
