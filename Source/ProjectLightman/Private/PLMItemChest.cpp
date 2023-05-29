// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMItemChest.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

// Sets default values
APLMItemChest::APLMItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	GoldMesh = CreateDefaultSubobject<UStaticMeshComponent>("GoldMesh");
	GoldMesh->SetupAttachment(BaseMesh);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetupAttachment(BaseMesh);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(BaseMesh);

	TargetPitch = 100.f;

}

// Called when the game starts or when spawned
void APLMItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLMItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APLMItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

