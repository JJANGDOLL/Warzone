// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_03.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_03 : public UScopeBase
{
	GENERATED_BODY()

public:
	UScope_03();

	ScopeBaseInheritance(TEXT("Scope-03"), EScopeType::SCOPE_03);
};
