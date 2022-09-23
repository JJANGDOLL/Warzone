// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "DamageText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ADamageText : public ATextRenderActor
{
	GENERATED_BODY()
	
public:
	ADamageText();
protected:
	void BeginPlay() override;

public:
	void SetText(FText Value, bool bCrit);
};
