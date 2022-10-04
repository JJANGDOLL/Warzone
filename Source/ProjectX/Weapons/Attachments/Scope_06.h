// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_06.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_06 : public UScopeBase
{
	GENERATED_BODY()
	
public:
	UScope_06();

	ScopeBaseInheritance(TEXT("Scope-06"), EScopeType::SCOPE_06);
};
