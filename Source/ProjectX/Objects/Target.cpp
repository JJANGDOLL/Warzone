// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Target.h"
#include "Utilities/Global.h"

ATarget::ATarget()
{
    Helpers::CreateComponent(this, &SkelComp, TEXT("Target"));

    USkeletalMesh* skelMesh;
    Helpers::GetAsset(&skelMesh, TEXT("SkeletalMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Environment/Objects/Target/SK_Target.SK_Target'"));
    SkelComp->SetSkeletalMesh(skelMesh);

    SkelComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    SkelComp->SetCollisionProfileName(TEXT("Body"));
    SkelComp->SetGenerateOverlapEvents(true);
    
    TSubclassOf<UAnimInstance> skelAnim;
    Helpers::GetClass(&skelAnim, TEXT("AnimBlueprint'/Game/ProjectX/Objects/ABP_Target.ABP_Target_C'"));
    SkelComp->SetAnimClass(skelAnim);
}

void ATarget::Hitted(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    bDown = true;
    if(bCanRecover)
        GetWorldTimerManager().SetTimer(RecoverHandle, this, &ATarget::Recover, 1.f, false, 3.f);
}

void ATarget::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SkelComp->OnComponentBeginOverlap.AddDynamic(this, &ATarget::Hitted);
}

void ATarget::Recover()
{
    GetWorldTimerManager().ClearTimer(RecoverHandle);
    bDown = false;
}

void ATarget::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATarget::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(RecoverHandle, this, &ATarget::Recover, 1.f, false, 0.f);
}
