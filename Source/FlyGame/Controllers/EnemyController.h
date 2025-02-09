// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAIPerceptionComponent;
class AEnemyPawn;
/**
 * 
 */
UCLASS()
class FLYGAME_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AIPerceptionComp")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyClass")
	TSubclassOf<AActor> TargetClass;

protected:
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetForgotten(AActor* Actor);

public:
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return Blackboard; }
};
