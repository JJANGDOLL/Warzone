// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_07.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_07 : public UScopeBase
{
	GENERATED_BODY()

public:
	UScope_07();

	ScopeBaseInheritance(TEXT("Scope-07"), EScopeType::SCOPE_07);
	
};
