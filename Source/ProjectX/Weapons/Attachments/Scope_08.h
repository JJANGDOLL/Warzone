// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_08.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_08 : public UScopeBase
{
	GENERATED_BODY()

public:
	UScope_08();

	ScopeBaseInheritance(TEXT("Scope-08"), EScopeType::SCOPE_08);

};
