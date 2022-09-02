// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViewmodelHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTZ_API UViewmodelHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UViewmodelHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void EventRefresh();
	bool CheckLocallyControlled(class AActor* Object);
	void UpdateMeshes();

private:
	TArray<class UActorComponent*> Meshes;
	bool bLocalCharacterControlled;
};
