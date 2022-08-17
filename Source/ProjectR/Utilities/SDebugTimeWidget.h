// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PROJECTR_API SDebugTimeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDebugTimeWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class ADebugTimeController>, OwnerActor);

	SLATE_END_ARGS()

public:
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	float GetGlobalTimeDilation(const UObject* WorldContextObject);
	TWeakObjectPtr<class ADebugTimeController> OwnerActor;

public:
    FText GetDilation() const;
    TAttribute<FText> _TimeDilation;

	FText IsPaused() const;
	TAttribute<FText> _Paused;
};
