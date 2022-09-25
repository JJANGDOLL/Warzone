// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/IWeaponAttachment.h"
#include "Engine/Texture2D.h"
#include "WeaponAttachment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UWeaponAttachment : public UStaticMeshComponent, public IIWeaponAttachment
{
	GENERATED_BODY()
	
public:
	UWeaponAttachment();



public:
	class UTexture2D* GetAttachmentImage() override;
};
