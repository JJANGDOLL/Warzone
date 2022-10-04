// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_04.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_04 : public UScopeBase
{
	GENERATED_BODY()

public:
	UScope_04();

	ScopeBaseInheritance(TEXT("Scope-04"), EScopeType::SCOPE_04);
};
