// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponScopeDA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UWeaponScopeDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Scope", meta = (AllowPrivateAccess = true))
	FTransform AimOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Scope", meta = (AllowPrivateAccess = true))
    float ScopeMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Scope", meta = (AllowPrivateAccess = true))
    class UTextureRenderTarget2D* TextureRender;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Scope", meta = (AllowPrivateAccess = true))
    class UStaticMesh* ScopeMesh;
};
