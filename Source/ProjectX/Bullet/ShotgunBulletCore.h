// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BulletBase.h"
#include "ShotgunBulletCore.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AShotgunBulletCore : public ABulletBase
{
	GENERATED_BODY()
	
public:
	void OnLaunch(bool bCinematic, FVector Velocity) override;

};
