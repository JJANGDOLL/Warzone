// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/AnimInst_Target.h"
#include "Target.h"

UAnimInst_Target::UAnimInst_Target()
{

}

void UAnimInst_Target::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Target = Cast<ATarget>(GetOwningActor());
    verifyf(Target, L"Invalid target");
}

void UAnimInst_Target::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!Target)
        return;
    bDown = Target->bDown;
}
