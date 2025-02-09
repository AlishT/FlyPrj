// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_RotateTurret.generated.h"

/**
 * 
 */
UCLASS()
class FLYGAME_API UBTT_RotateTurret : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_RotateTurret(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
