// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponAttachment.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "ScopeTemp.generated.h"

/**
 * 
 */
class UWeaponScopeDA;
class UDataTable;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()
class PROJECTX_API UScopeTemp : public UWeaponAttachment
{
	GENERATED_BODY()
	
public:
	UScopeTemp();



	void BeginPlay() override;

protected:
	EScopeType SetScopeType();
    FName SetScopeName();

	void GetFOV(UDataTable* ScopeDT);
	bool FindScopeDataInDataTable();


public:
	FTransform GetScopeOffset(UDataTable* ScopeDT);
	void EnableScope(UDataTable* ScopeDT);

private:
	EScopeType ScopeType;
	FName ScopeName;
	UWeaponScopeDA* ScopeDA;
	FTransform ScopeAimOffset;
	float ScopeFOV;

	USceneCaptureComponent2D* SceneCaptureScope;
    UTextureRenderTarget2D* TextureRender;

	
};
