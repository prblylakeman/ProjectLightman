// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMGameModeBase.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryManager.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/PLMAICharacter.h"
#include "PLMAttributeComponent.h"
#include "EngineUtils.h"

APLMGameModeBase::APLMGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void APLMGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &APLMGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void APLMGameModeBase::SpawnBotTimerElapsed()
{
	int32 LivingBotCount = 0;
	for (TActorIterator<APLMAICharacter> It(GetWorld()); It; ++It)
	{
		APLMAICharacter* AIBot = *It;

		UPLMAttributeComponent* AttributeComponent = UPLMAttributeComponent::GetAttributes(AIBot);

		if (AttributeComponent && AttributeComponent->IsAlive())
		{
			LivingBotCount++;
		}
	}

	float MaxBotCount = 8.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (LivingBotCount >= MaxBotCount)
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &APLMGameModeBase::OnQueryCompleted);
	}
}

void APLMGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed!"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}

}
