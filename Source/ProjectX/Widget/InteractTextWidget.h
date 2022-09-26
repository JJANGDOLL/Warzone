// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractTextWidget.generated.h"

/**
 * 
 */

class UEditableText;

UCLASS()
class PROJECTX_API UInteractTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInteractText(FText InText);

    UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableText* InteractText;
};
