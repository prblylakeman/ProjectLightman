// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PLMAICharacter.h"
#include "AIModule/Classes/Perception/PawnSensingComponent.h"
#include "AIModule/Classes/AIController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APLMAICharacter::APLMAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

}

void APLMAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &APLMAICharacter::OnPawnSeen);
}

void APLMAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
	}
}

// Called when the game starts or when spawned
void APLMAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLMAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

