#pragma once

#include "Misc/EnumRange.h"

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
    None,
    ASSAULT_RIFLE_01,
    ASSAULT_RIFLE_02,
    ASSAULT_RIFLE_03,
    HANDGUN_01,
    HANDGUN_02,
    SHOTGUN_01,
    SNIPER_01,
    SNIPER_02,
    SNIPER_03,
    SMG_01,
    Count UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EWeaponTypes, EWeaponTypes::Count);

inline uint8 GetTypeHash(const EWeaponTypes& rhs)
{
    return (uint8)rhs;
}

UENUM(BlueprintType)
enum class EWeaponFeature : uint8
{
    None = 0,
    Reload,
    Fire,
    EjectingCasing,
    SpawnBullet,
    SpawnFlame,
    Count UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
    None = 0,
    Single,
    Brust,
    Auto,
    Count UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EFireType, EFireType::Count);

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
    None = 0,
    Big,
    Small,
    Count UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EScopeType : uint8
{
    None = 0,
    SCOPE_01,
    Count UMETA(Hidden)
};