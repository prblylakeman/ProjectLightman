// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PLMAICharacter.h"
#include "AIModule/Classes/Perception/PawnSensingComponent.h"
#include "AIModule/Classes/AIController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "PLMAttributeComponent.h"
#include "BrainComponent.h"

// Sets default values
APLMAICharacter::APLMAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComponent = CreateDefaultSubobject<UPLMAttributeComponent>("AttributeComponent");

}

void APLMAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &APLMAICharacter::OnPawnSeen);

	AttributeComponent->OnChangeInitiated.AddDynamic(this, &APLMAICharacter::OnChangeInitiated);
}



// Called when the game starts or when spawned
void APLMAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APLMAICharacter::OnChangeInitiated(AActor* InstigatorActor, UPLMAttributeComponent* OwningComponent, int NewHealth, int Delta)
{
	if (Delta < 0)
	{

		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}


		if (NewHealth <= 0)
		{
			AAIController* AIController = Cast<AAIController>(GetController());

			if (AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}
			
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");


			SetLifeSpan(8.0f);
		}
	}
}

void APLMAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void APLMAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	//DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
}

// Called every frame
void APLMAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

