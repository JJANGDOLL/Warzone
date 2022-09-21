#pragma once

UENUM(BlueprintType)
enum class ECharacterFeature : uint8
{
    None = 0,
    Aiming,
    Fire,
    Reload,
    ReloadEmpty,
    Running,
    Count UMETA(Hidden)
};