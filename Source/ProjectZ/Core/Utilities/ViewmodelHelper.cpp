// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Utilities/ViewmodelHelper.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UViewmodelHelper::UViewmodelHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.TickInterval = 0.05f;


}


// Called when the game starts
void UViewmodelHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Meshes = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());



// 	while (true)
// 	{
// 		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), GetComponentTickInterval(), FLatentActionInfo());
// 
// 	}
}

void UViewmodelHelper::EventRefresh()
{
	if (GetOwner()->IsChildActor())
	{
		if (CheckLocallyControlled(GetOwner()->GetParentActor()))
		{
			bLocalCharacterControlled = true;
		}
		else
		{
			bLocalCharacterControlled = CheckLocallyControlled(GetOwner()->GetParentActor()->GetAttachParentActor());
		}
	}
	else
	{
		bLocalCharacterControlled = CheckLocallyControlled(GetOwner()->GetAttachParentActor());
	}

	UpdateMeshes();
}

bool UViewmodelHelper::CheckLocallyControlled(AActor* Object)
{
	if (!Object)
		return false;

	APawn* controlledPawn = Cast<APawn>(Object);
	if (!controlledPawn)
		return false;
	return controlledPawn->IsLocallyControlled();
}

void UViewmodelHelper::UpdateMeshes()
{
	for (auto& elem : Meshes)
	{
		UStaticMeshComponent* LocalMesh;
		LocalMesh = Cast<UStaticMeshComponent>(elem);

		LocalMesh->SetScalarParameterValueOnMaterials(TEXT("Field Of View Alpha"), bLocalCharacterControlled);
		LocalMesh->SetBoundsScale(bLocalCharacterControlled ? 1.f : 4.f);
	}
}
