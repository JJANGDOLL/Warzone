// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponAttachment.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "Datas/Weapons/WeaponScopeDA.h"
#include "ScopeBase.generated.h"

#define ScopebaseConstruct(ClassName) \
ClassName::ClassName()\
{\
SetScopeName();\
SetScopeType();\
}\

#define ScopeBaseInheritance(Name, Type) \
protected:\
virtual void SetScopeName()\
{\
ScopeName = Name;\
}\
virtual void SetScopeType()\
{\
ScopeType = Type;\
}\

class UWeaopnScopeDA;
class UStaticMesh;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
class UDataTable;

UCLASS(Abstract)
class PROJECTX_API UScopeBase : public UWeaponAttachment
{
	GENERATED_BODY()

public:
	UScopeBase();

protected:
	virtual void SetScopeName(); // PURE_VIRTUAL(UScopeBase::SetScopeName, ;);
	virtual void SetScopeType(); // PURE_VIRTUAL(UScopeBase::SetScopeType, ;);

public:
	void EnableScope(UDataTable* ScopeDT);
	FTransform GetScopeOffset();
	UStaticMesh* GetScopeMesh();

protected:
	EScopeType ScopeType;
	FName ScopeName;
	UWeaponScopeDA* ScopeDA;
	FTransform ScopeAimOffset;
	float ScopeFOV;
	UStaticMesh* ScopeMesh;

	USceneCaptureComponent2D* ScopeSceneCapture;
	UTextureRenderTarget2D* ScopeTextureRender;
};
