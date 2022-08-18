// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/IWeapon.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UStaticMeshComponent;
class UAnimMontage;
class UTexture;

UCLASS(Abstract)
class PROJECTR_API AWeaponBase : public AActor, public IIWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* MeshWeapon;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SocketDefault;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MeshIronsight;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SocketMagazine;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MeshMagazine;

protected:
	//Should this Weapon be automatic?
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Settings")
	bool bAutomatic;

	//Amount of rounds per minute that the Weapon can fire.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Settings")
	float RateOfFire;

	//Maximum ammunition that the Weapon's magazine can hold.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Settings")
	int AmmunitionMax;

	//Firing Montage.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Animation")
	UAnimMontage* MontageFire;

	//Reload Montage.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Animation")
	UAnimMontage* MontageReload;

	//Reload Empty Montage. Played when reloading without any leftover ammunition.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Animation")
	UAnimMontage* MontageReloadEmpty;

	//Texture displayed in the player's heads up display to represent this Weapon's shape/body.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Display")
	UTexture* TextureWeaponBody;

	//Texture displayed in the player's heads up display to represent this Weapon's magazine.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Display")
	UTexture* TextureWeaponMagazine;

	//Texture displayed in the player's heads up display to represent this Weapon's ironsights.
	UPROPERTY(BlueprintReadOnly, Category = " Weapon | Display")
	UTexture* TextureWeaponIronsights;

	//Result from hitting something when firing.
	UPROPERTY(BlueprintReadWrite, Category = " Weapon | Data")
	FHitResult HitResult;

	//Current amount of bullets in the magazine.
	UPROPERTY(BlueprintReadWrite, Category = " Weapon | Data")
	int AmmunitionCurrent;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon | Particle")
	UParticleSystem* ParticleMuzzleFlash;

public:
	void OnFire() override;
	void OnReload() override;
	bool IsAutomatic() override;
	uint8 GetAmmunitionCurrent() override;
	uint8 GetAmmunitionTotal() override;
	float GetRateOfFire() override;
	bool IsEmpty() override;
	UTexture* GetTextureWeaponBody() override;
	UTexture* GetTextureWeaponMagazine() override;
	UTexture* GetTextureWeaopnIronsight() override;
};
