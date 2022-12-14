#pragma once

#include "WeaponsEnum.h"
#include "Engine/DataTable.h"

#include "WeaponsStructs.generated.h"

USTRUCT(BlueprintType)
struct FWeaponDARef : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPrimaryDataAsset* DataRef;
};

USTRUCT(BlueprintType)
struct FWeaponScopeDARef : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EScopeType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UPrimaryDataAsset* DataRef;
};