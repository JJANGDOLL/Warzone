// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BulletBase.h"
#include "TurretBullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ATurretBullet : public ABulletBase
{
	GENERATED_BODY()
	
public:
	ATurretBullet();
protected:
	void BeginPlay() override;


	class ACharacter* PlayerCharacter;
};
