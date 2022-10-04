// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Attachments/Scope_01.h"

UScope_01::UScope_01()
{
    SetScopeName();
    SetScopeType();
}

void UScope_01::SetScopeName()
{
    ScopeName = TEXT("Scope-01");
}

void UScope_01::SetScopeType()
{
    ScopeType = EScopeType::SCOPE_01;
}
