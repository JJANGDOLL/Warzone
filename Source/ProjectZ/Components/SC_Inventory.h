// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Core/Defines/Structs.h"
#include "Core/Defines/Enums.h"
#include "SC_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquippedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnedStartingItems);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHolstering);

class AActor;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTZ_API USC_Inventory : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USC_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float InitialUnholsterDelay = 0.5f;

public:
	void EventServerSpawnItems();
	void SpawnInitialItems();
	void EquipItem(class AActor* Item);
	void SetEquippedItem(class AActor* Item);
	AActor* GetEquipped();

public:
	bool bSpawnedInitial;
	TArray<FSInventoryStartingItem> StartingItems;
	TArray<class AActor*> Inventory;
	int32 EquippedIndexAtStart;
	class AActor* Equipped;
	FEquippedDelegate OnEquipped;
	bool bStarted;
	FSpawnedStartingItems OnSpawnStartingItems;

public:
	void EventServerUnholsterWithName(FName InUnholsterName);
	bool TryStartHolsterAbility();
	class APawn* GetPawnOwner();
	void EventMulticastUnholster();
	void EventUnholster();
	void EventUnholsterCore();
	void GetAnimationMontagefromDataTable(UDataTable* Table, FName Name, bool& OutIsValid, UAnimMontage** OutMontageFirstPerson, UAnimMontage** OutMontageThirdPerson);
	class USkeletalMeshComponent* GetCharacterMesh();
	void EventSetFullyHolstered(bool InFullyHolstered);

public:
	FName UnholsterName;
	APawn* PawnOwner;
	EWeaponHolsterState HolsterState;
	FHolstering OnHolstering;
	class USkeletalMeshComponent* FirstPersonMesh;
	bool FullyHolstered;

public:
	void EventServerTryDropEquipped();
	void TryDropEquipped(bool PlayDropAnimation);
	void DropEquipped();
	void StopAllOwnerMontage();

public:
	bool bCanDropItems;
	float DroppingForce;
	FVector DroppingForceAngular;

public:
	void EventServerTryEquipItemAdded(int32 Added);
	void TryEquipItemAdded(int32 Added);
	int32 GetEquippedIndex();
	void EventTryEquipItem(int32 Index, bool bHolster);
	void EventTryEquipItemCore();
	EWeaponHolsterState GetHolsterState();
	void EventMulticastHolster();
	void SetRefreshUnholster(bool InRefreshUnholster);
	void EventHolster();
	void EventHolsterCore();
	FName GetNameMontageHolster();

public:
	int32 NextAdded;
	bool bEquippingHolster;
	int32 EquippingItem;
	FSGameAbility SwappingAbility;
	bool bRefreshUnholster;
	FName HolsterName;

public:
	void EventServerTryPickupItem(AActor* Item);
	void TryPickUpItem(AActor* Item);
	bool HasSpace();

public:
	int32 InventoryCapacity;

public:
	void EventServerTryEquipItem(int32 ItemIndex);

public:
	void EventServerTryEquipNextItem();
	int32 GetNextItemIndex();

public:
    void EventServerTryEquipPrevItem();
	int32 GetPrevItemIndex();

public:
	void EventServerUnholster();
	FName GetNameMontageUnholster();

};
