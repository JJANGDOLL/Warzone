// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tests/WeaponCoreTest.h"
#include "Utilities/Global.h"

AWeaponCoreTest::AWeaponCoreTest()
{

}

void AWeaponCoreTest::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TestActionHandle, this, &AWeaponCoreTest::TestAction, 2.0f, true);

    PrintLine();
}

void AWeaponCoreTest::Test()
{

    PrintLine();
}
