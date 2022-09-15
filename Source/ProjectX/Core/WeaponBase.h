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

	void DoNothing();
	void Reload() override;
	void Fire() override;
	void EjectCasing() override;
	void SpawnBullet() override;
	void SpawnFlame() override;

	FVector GetWeaponForward() override;

	UWeaponPoseDA* GetPosesDA() override;

    USkeletalMeshComponent* GetWeaponBodyMesh();
    UStaticMeshComponent* GetWeaponMagazineMesh();
    UStaticMeshComponent* GetWeaponIronSightMesh();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Weapon | Opt", meta = (AllowPrivateAccess=true))
	float EjectImpulse = 350.f;
};

