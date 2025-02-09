
#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FlyGame/Pawns/EnemyPawn.h"

AEnemyController::AEnemyController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	check(BehaviorTreeComp);

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard "));
	check(BlackboardComp);

	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetDetected);
	AIPerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyController::OnTargetForgotten);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn) return;

	AEnemyPawn* AIPawn = Cast<AEnemyPawn>(InPawn);

	if (AIPawn->GetBehaviorTree())
	{
		BlackboardComp->InitializeBlackboard(*(AIPawn->GetBehaviorTree()->BlackboardAsset));

		BehaviorTreeComp->StartTree(*(AIPawn->GetBehaviorTree()));
	}
}

void AEnemyController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->IsA(TargetClass))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			SetFocus(Actor);
			FVector EnemyLocation = Actor->GetActorLocation();

			BlackboardComp->SetValueAsObject(TEXT("Target"), Actor);
			BlackboardComp->SetValueAsBool(TEXT("bEnemyDetected"), true);
			Blackboard->SetValueAsVector(TEXT("TargetLocation"), EnemyLocation);
		}
		else
		{
			BlackboardComp->ClearValue(TEXT("Target"));
		}
	}
}

void AEnemyController::OnTargetForgotten(AActor* Actor)
{
	ClearFocus(EAIFocusPriority::LastFocusPriority);

	Actor = nullptr;

	SetFocus(nullptr);
	BlackboardComp->SetValueAsObject(TEXT("Target"), Actor);
}
