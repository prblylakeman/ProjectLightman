// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PLMBTService_CheckAttackRange.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"

void UPLMBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
			if (TargetActor)
			{
				AAIController* AIController = OwnerComp.GetAIOwner();
					if (ensure(AIController))
					{
						APawn* AIPawn = AIController->GetPawn();
							if (ensure(AIPawn))
							{
								float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
								
								bool bWithinRange = DistanceTo < 2600.f;

								bool bHasLineOfSight = false;

								if (bWithinRange)
								{
									bHasLineOfSight = AIController->LineOfSightTo(TargetActor);
								}

								BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLineOfSight));
							}
					}
			}
	}
}
