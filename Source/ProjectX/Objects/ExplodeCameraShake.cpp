// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ExplodeCameraShake.h"

UExplodeCameraShake::UExplodeCameraShake()
{
    OscillationDuration = 0.25f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::FRandRange(5.f, 10.f);
    RotOscillation.Pitch.Frequency= FMath::FRandRange(5.f, 35.f);

    RotOscillation.Yaw.Amplitude = FMath::FRandRange(5.f, 10.f);
    RotOscillation.Yaw.Frequency = FMath::FRandRange(5.f, 35.f);
}

