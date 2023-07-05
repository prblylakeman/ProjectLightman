// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PLMBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHTMAN_API UPLMBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	
protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
