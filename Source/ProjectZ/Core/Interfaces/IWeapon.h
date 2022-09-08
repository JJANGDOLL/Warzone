// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "Core/Defines/Structs.h"
#include "IWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UIWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTZ_API IIWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual void OnSpawnAttachmentComponents() = 0;
	virtual void OnChangeSettingsPhysicalAttachments(FDataTableRowHandle Value) = 0;
	virtual void OnChangeSettingsPhysicalBody(FDataTableRowHandle Value) = 0;
	virtual void OnAimingStop() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEquipped() = 0;
	virtual void OnUnequipped() = 0;
	virtual void OnUpdateAmmunition(bool Fill, int32 Amount) = 0;
	virtual int32 GetAmmunitionTotal() = 0;
	virtual bool IsOutOfAmmunition() = 0;
	virtual void OnSaveLoadout() = 0;
	virtual void OnWeaponDrop(FVector ThrowImpulse, FVector AngularImpulse) = 0;
	virtual void OnEquipSavedLoadout() = 0;
	virtual void OnRandomizePreset() = 0;
	virtual void OnMontagePlay(FName Name, bool FirstPerson) = 0;
	virtual void OnChangeSettingsPhysical(FDataTableRowHandle RowHandle) = 0;
	virtual FSAbilities GetCharacterAbilities() = 0;
	virtual UDataTable* GetCharacterAnimationMontages() = 0;
	virtual void OnMontageStopAll(float BlendTime) = 0;
	virtual void OnStopAudioPlaying() = 0;
	virtual FSAnimationSettings GetSettingsAnimation() = 0;
	virtual class USkeletalMeshComponent* GetStaticMeshBody() = 0;
	virtual class UDataTable* GetCharacterAnimationPoses() = 0;
	virtual FSScope GetSettingsScope() = 0;
	virtual FSGrip GetSettingsGrip() = 0;
	virtual FSMovement GetCharacterSettingsMovement() = 0;
};
