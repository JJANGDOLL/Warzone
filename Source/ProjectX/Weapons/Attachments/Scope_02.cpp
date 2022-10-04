// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Attachments/Scope_02.h"

UScope_02::UScope_02()
{
    SetScopeName();
    SetScopeType();
}

void UScope_02::SetScopeName()
{
    ScopeName = TEXT("Scope-02");
}

void UScope_02::SetScopeType()
{
    ScopeType = EScopeType::SCOPE_02;
}
