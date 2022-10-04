// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Attachments/ScopeBase.h"
#include "Scope_02.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UScope_02 : public UScopeBase
{
	GENERATED_BODY()

public:
	UScope_02();
	
protected:
	void SetScopeName() override;


	void SetScopeType() override;

};
