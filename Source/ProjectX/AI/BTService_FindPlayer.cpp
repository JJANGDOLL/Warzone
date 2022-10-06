// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindPlayer.h"
#include "Core/EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
    bCreateNodeInstance = true;
}

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto enemyAIController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

    if (!enemyAIController)
        return;

    auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(enemyAIController->TargetKeyID, playerPawn);
}
