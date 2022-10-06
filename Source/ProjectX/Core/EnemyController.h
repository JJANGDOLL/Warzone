
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	

private:
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

public:
	AEnemyController();

	
	FBlackboard::FKey TargetKeyID;
protected:
	void OnPossess(APawn* InPawn) override;
};
