// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MoveToPlayer.h"
#include "Core/EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "GameFramework/Character.h"

UBTTask_MoveToPlayer::UBTTask_MoveToPlayer()
{
    NodeName = TEXT("Move To Player");
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    auto enemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
    auto blackBoard = OwnerComp.GetBlackboardComponent();

    ACharacter* target = Cast<ACharacter>(blackBoard->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));

    if (target)
    {
        enemyController->MoveToActor(target, 50.f);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
