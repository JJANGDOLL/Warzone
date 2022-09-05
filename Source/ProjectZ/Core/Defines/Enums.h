#pragma once

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
    SMG,
    AssaultRifle,
    Handgun,
    Granades,
    Launcher,
    Sniper,
    Shotgun
};

UENUM(BlueprintType)
enum class EFireMode : uint8
{
    Semi,
    Automatic,
    Burst,
    BurstHold,
    Safe
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
    None,
    WeaponPickup,
    AmmunitionRefill
};

UENUM(BlueprintType)
enum class EWeaponHolsterState : uint8
{
    Available,
    Holstered
};