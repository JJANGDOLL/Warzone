// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Inventory.generated.h"

class IIMainWeapon;
class IIItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTX_API UAC_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	uint8 SelectedIdx = 0;

	IIItem* LastItem;

	TArray<IIItem*> Inventory;

public:
	IIItem* GetLastItem();
	IIItem* GetSelectedItem(uint8 Idx);
	void PutItem(IIItem* InItem);
};
