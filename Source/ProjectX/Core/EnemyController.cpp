// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/EnemyController.h"
#include "Utilities/Global.h"
#include "EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyController::AEnemyController()
{
    Helpers::CreateActorComponent(this, &BlackboardComp, TEXT("BlackboardComp"));
    Helpers::CreateActorComponent(this, &BehaviorComp, TEXT("BehaviorComp"));
}

void AEnemyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    auto character = Cast<AEnemyBase>(InPawn);

    if (character && character->EnemyBehaviorTree)
    {
        BlackboardComp->InitializeBlackboard(*character->EnemyBehaviorTree->BlackboardAsset);

        TargetKeyID = BlackboardComp->GetKeyID(TEXT("Target"));
        BehaviorComp->StartTree(*character->EnemyBehaviorTree);
    }
}
