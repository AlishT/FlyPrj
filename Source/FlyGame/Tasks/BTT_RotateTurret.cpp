// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_RotateTurret.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FlyGame/Controllers/EnemyController.h"
#include "FlyGame/Pawns/EnemyPawn.h"

UBTT_RotateTurret::UBTT_RotateTurret(const FObjectInitializer& ObjectInitializer)
{
}

EBTNodeResult::Type UBTT_RotateTurret::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AEnemyController* AIConrtoler = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (AIConrtoler)
	{
		AEnemyPawn* AIPawn = Cast<AEnemyPawn>(AIConrtoler->GetPawn());

		if (AIPawn)
		{
			if (!AIConrtoler->GetFocusActor())
			{
				return EBTNodeResult::Failed;
			}

			FVector TargetLocation = AIConrtoler->GetFocusActor()->GetActorLocation();
			
			AIPawn->SetTargetLocation(TargetLocation);
			AIPawn->RotateTurret();
			AIPawn->RotateWeapon();
		}
	}

	return EBTNodeResult::Succeeded;
}