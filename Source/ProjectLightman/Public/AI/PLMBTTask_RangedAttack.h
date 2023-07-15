// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PLMBTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIGHTMAN_API UPLMBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxProjectileSpread;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxProjectilePitch;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> ProjectileClass;

public:

	UPLMBTTask_RangedAttack();
	
};
