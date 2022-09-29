// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "UObject/WeakInterfacePtr.h"
#include "AC_Inventory.generated.h"


class IIMainWeapon;
class IIItem;
class UIItem;
class AWeaponBase;


DECLARE_DELEGATE(FWeaponChangeDelegate);
DECLARE_DELEGATE(FNeedWidgetUpdate);

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
	IIItem** CurrentItem;
// 	TWeakObjectPtr<IIItem*> CurrentItem;

	TArray<IIItem*> Inventory;

	uint32 BigBullet = 150;
	uint8 SmallBullet = 80;
	bool bWeaponChanged = false;

public:
	IIItem* GetLastItem();
	IIItem* GetSelectedItem(uint8 Idx);
	void SetSelectedItem(uint8 Idx);
	void PutItem(IIItem* InItem);
	uint32 GetRemainAmmo(EAmmoType AmmoType);
	void SetRemainAmmo(EAmmoType AmmoType, uint32 UseAmmo);
	void SetMaxAmmo(EAmmoType AmmoType);
	void DropItem(bool bNextWeapon = true);
	void PickupItem(IIItem* PickupItem);

	void AddWeapon(TSubclassOf<AWeaponBase> WeaponClass, uint8 Idx);

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IIItem* GetCurrentItem();

	bool IsWeaponChanged();

public:
	FWeaponChangeDelegate OnWeaponChanged;
	FNeedWidgetUpdate OnWidgetUpdate;
};
