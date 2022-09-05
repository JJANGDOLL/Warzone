// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_Interactor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Core/Interfaces/IInteractable.h"
#include "Core/Interfaces/IInteractorTarget.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UAC_Interactor::UAC_Interactor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bEnabled = true;
	Radius = 5.f;


	ObjectTypesForward.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypesForward.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel6));

    ObjectTypesBelow.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
    ObjectTypesBelow.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel6));

	Location = FVector::ZeroVector;
	Forward = FVector::ZeroVector;

	Type = EInteractionType::None;
}


// Called when the game starts
void UAC_Interactor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
}


// Called every frame
void UAC_Interactor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!Owner)
		return;

	IIInteractorTarget* interactTarget = Cast<IIInteractorTarget>(Owner);
	if (!interactTarget)
		return;

	interactTarget->GetInteractVectors(Location, Forward);
	Trace();

	Character = Cast<ACharacter>(Owner);
}

void UAC_Interactor::ResetType()
{
	Type = EInteractionType::None;
}

void UAC_Interactor::TryAssignType()
{
	IIInteractable* interact = Cast<IIInteractable>(HitResult.Actor);
	if (!interact)
		return;

	if (interact->CanInteract())
	{
		Type = interact->GetIteractionType();
	}
	else
	{
		ResetType();
	}
}

FHitResult UAC_Interactor::GetHitResult()
{
	return HitResult;
}

EInteractionType UAC_Interactor::GetType()
{
	return Type;
}

void UAC_Interactor::Trace()
{
	if (!bEnabled)
	{
		ResetType();
		return;
	}

	IIInteractorTarget* interactTarget = Cast<IIInteractorTarget>(Owner);

	if (!interactTarget)
	{
		ResetType();
		return;
	}

	if (!interactTarget->CanTraceInteraction())
	{
		ResetType();
		return;
	}

	TArray<AActor*> tChar;
	tChar.Add(Character);

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Location, Location + (Forward * Distance), Radius, ObjectTypesForward, false, tChar, EDrawDebugTrace::None, HitResult, true))
	{
		TryAssignType();
	}
	else
	{
		if (!Character)
		{
			ResetType();
			return;
		}

		FVector tVec = Character->GetCapsuleComponent()->GetComponentLocation() - FVector(0.f, 0.f, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), tVec, tVec, Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), ObjectTypesBelow, false, tChar, EDrawDebugTrace::None, HitResult, true);

		TryAssignType();
	}
}

