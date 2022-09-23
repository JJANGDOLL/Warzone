// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "Interfaces/IWeapon.h"
#include "WeaponBase.generated.h"

class UWeaponBody;
class UWeaponMagazine;
class UWeaponDA;
class USceneComponent;
class UWeaponAttachment;
class ACasingBase;
class ABulletBase;
class UParticleSystem;
class UWeaponPoseDA;
class USoundCue;
class UTexture;

UCLASS(Abstract)
class PROJECTX_API AWeaponBase : public AActor, public IIWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	UPROPERTY()
	UWeaponBody* Weapon;

	UPROPERTY()
	USceneComponent* SocketMagazine;

	UPROPERTY()
	UWeaponMagazine* Magazine;

	UPROPERTY()
	USceneComponent* SocketIronSight;

	UPROPERTY()
	UWeaponAttachment* IronSight;

protected:
	UPROPERTY()
	EWeaponTypes WeaponType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void MakeWeapon();
	void GetWeaponNameByWeaponType();
	bool FindWeaponDataInDataTable();
	void GetWeaponBody();
	void GetWeaponMagazine();
	void GetWeaponIronsight();
	void GetCasingInfo();
    void GetBulletInfo();
	void GetFlame();
	void GetPoses();
    UAnimSequenceBase* GetEmptyPose();
	void GetWeaponInfo();
    void GetSounds();

	virtual void SetWeaponName();

protected:
	FName WeaponName;
	class UWeaponDA* WeaponDA;

protected:
	FTimerHandle TestTimerHandle;

private:
	typedef void (AWeaponBase::*TestFunc)(void);
	TMap<EWeaponFeature, TestFunc> TestMethods;

    UPROPERTY(EditInstanceOnly, Category = "Projx | Weapon | Test", meta=(AllowPrivateAccess=true))
	EWeaponFeature TestFeature;

public:
	TestFunc OnTestFeature = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Test", meta = (AllowPrivateAccess=true))
	float TestTerm = 5.f;

	TSubclassOf<ACasingBase> CasingClass;
	TSubclassOf<ABulletBase> BulletClass;
	UParticleSystem* Flame;
	UWeaponPoseDA* PosesDA;
	FTransform AimOffset;

	void DoNothing();
	void Reload() override;
	void Fire() override;
	void EjectCasing() override;
	void SpawnBullet() override;
	void SpawnFlame() override;
    bool IsEmpty() override;

	FVector GetWeaponForward() override;

	UWeaponPoseDA* GetPosesDA() override;
	FTransform GetAimOffset() override;
    int8 GetMaxAmmo() override;
	int8 GetCurAmmo() override;
	EFireType GetFireType() override;
	float GetFireInterval() override;
	bool IsReloading() override;
    UTexture2D* GetWeaponBodyImage() override;


    USkeletalMeshComponent* GetWeaponBodyMesh();
    UStaticMeshComponent* GetWeaponMagazineMesh();
    UStaticMeshComponent* GetWeaponIronSightMesh();

	void SetAmmo(int8 InAmmo);
	void ChangeFireType();
	void OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess=true))
	float EjectImpulse = 350.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
	uint8 MaxAmmo = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
	uint8 CurrentAmmo = 5;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
	uint8 FireTypeIdx = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
	bool bReloading = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
    USoundCue* FireSound;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
    USoundCue* ReloadSound;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess = true))
    USoundCue* ReloadEmptySound;
};


