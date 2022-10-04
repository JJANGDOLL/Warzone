// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_05.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_05 : public UScopeBase
{
	GENERATED_BODY()

	ScopeBaseInheritance(TEXT("Scope-05"), EScopeType::SCOPE_05);

public:
	UScope_05();

};
