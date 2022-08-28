// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugTimeController.generated.h"

UCLASS()
class PROJECTZ_API ADebugTimeController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebugTimeController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void TestFunc();
	void BindToInput();
	void IncreaseTimeSclae();
	void DecreaseTimeSclae();
	void UpdateTimeScale(float InValue);
	void Pause();

private:
	float _TimeScaleDefault = 1.0f;
	float _TimeScaleIncrements = 0.1f;
	float _TimeScaleCurrent = 0.0f;
	bool _bPaused;

private:
	TSharedPtr<class SDebugTimeWidget> _ui;

public:
	float GetTimeScale();
	bool IsPaused();
};
