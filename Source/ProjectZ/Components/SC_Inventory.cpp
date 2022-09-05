// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SC_Inventory.h"
#include "Engine/DataTable.h"
#include "Core/Interfaces/IWeapon.h"
#include "Utilities/Helper.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Core/Interfaces/ICharacter.h"
#include "Animation/AnimMontage.h"
#include "Core/Interfaces/IInventoryTarget.h"
#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"
#include "Core/Interfaces/IInteractable.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USC_Inventory::USC_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USC_Inventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	EventServerSpawnItems();

    UKismetSystemLibrary::Delay(GetWorld(), InitialUnholsterDelay, FLatentActionInfo());

}


// Called every frame
void USC_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USC_Inventory::EventServerSpawnItems()
{
	SpawnInitialItems();
}

void USC_Inventory::SpawnInitialItems()
{
	if (bSpawnedInitial)
		return;

	bSpawnedInitial = true;

	for (auto& startingItem : StartingItems)
	{
		FDataTableRowHandle inventorySlot = startingItem.InventorySlot;
		TArray<FName> tableNames = inventorySlot.DataTable->GetRowNames();
		FName inventorySlotRowName = startingItem.bRandomize ? tableNames[FMath::RandRange(0, tableNames.Num() - 1)] : inventorySlot.RowName;

		FSInventorySlot* findInventory = inventorySlot.DataTable->FindRow<FSInventorySlot>(inventorySlotRowName, "");
		if(!findInventory)
			continue;

		AActor* currentItem = GetWorld()->SpawnActor(findInventory->Item);
		IIWeapon* weaponIntf = Cast<IIWeapon>(currentItem);
		if (!weaponIntf)
			continue;

		FDataTableRowHandle physicsRowHandle;
		static UDataTable* physicsDT;
		if(!physicsDT)
			Helpers::GetAssetDynamic(&physicsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));
		physicsRowHandle.DataTable = physicsDT;
		physicsRowHandle.RowName = TEXT("Hidden");

		weaponIntf->OnChangeSettingsPhysical(physicsRowHandle);

		Inventory.Add(currentItem);
		currentItem->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	EquipItem(Inventory[EquippedIndexAtStart]);
}

void USC_Inventory::EquipItem(class AActor* Item)
{
	SetEquippedItem(Item);

	IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());
	if (!weaponItf)
		return;

	weaponItf->OnEquipped();

    FDataTableRowHandle physicsRowHandle;
    static UDataTable* physicsDT;
    if (!physicsDT)
        Helpers::GetAssetDynamic(&physicsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));

    physicsRowHandle.DataTable = physicsDT;
    physicsRowHandle.RowName = TEXT("Viewmodel");

	weaponItf->OnChangeSettingsPhysical(physicsRowHandle);
}

void USC_Inventory::SetEquippedItem(class AActor* Item)
{
	Equipped = Item;

	if (!GetEquipped())
		return;

	if (OnEquipped.IsBound())
		OnEquipped.Broadcast();

	if (!bStarted)
	{
        if (OnSpawnStartingItems.IsBound())
			OnSpawnStartingItems.Broadcast();
		bStarted = true;
	}
}

AActor* USC_Inventory::GetEquipped()
{
	return Equipped;
}

void USC_Inventory::EventServerUnholsterWithName(FName InUnholsterName)
{
	UnholsterName = InUnholsterName;

	if (!TryStartHolsterAbility())
		return;

	HolsterState = EWeaponHolsterState::Available;


}

bool USC_Inventory::TryStartHolsterAbility()
{
	IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());

	verifyf(weaponItf, L"invalid equipped weapon");

	FSAbilities charAbilities = weaponItf->GetCharacterAbilities();

	IICharacter* charItf = Cast<IICharacter>(GetPawnOwner());
	verifyf(charItf, L"invalid character pawn");

	return charItf->TryStartAbility(charAbilities.AbilityHolster);
}

class APawn* USC_Inventory::GetPawnOwner()
{
	if (PawnOwner)
		return PawnOwner;

	APawn* pawn = Cast<APawn>(GetOwner());
	verifyf(pawn, TEXT("invalid pawn owner"));

	PawnOwner = pawn;

	return PawnOwner;
}

void USC_Inventory::EventMulticastUnholster()
{
	EventUnholster();
}

void USC_Inventory::EventUnholster()
{
	EventUnholsterCore();
}

void USC_Inventory::EventUnholsterCore()
{
	IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());

	verifyf(weaponItf, TEXT("invalid equipped weapon"));

	UDataTable* charAnimDT = weaponItf->GetCharacterAnimationMontages();

	bool isValid;
	UAnimMontage* montageFirstPerson = nullptr;
	GetAnimationMontagefromDataTable(charAnimDT, UnholsterName, isValid, &montageFirstPerson, nullptr);

	if (OnHolstering.IsBound())
		OnHolstering.Broadcast();

	GetCharacterMesh()->GetAnimInstance()->Montage_Play(montageFirstPerson);

	EventSetFullyHolstered(false);

	weaponItf->OnMontagePlay(UnholsterName, true);
}

void USC_Inventory::GetAnimationMontagefromDataTable(UDataTable* Table, FName Name, bool& OutIsValid, UAnimMontage** OutMontageFirstPerson, UAnimMontage** OutMontageThirdPerson)
{
    OutIsValid = false;
    OutMontageFirstPerson = nullptr;
    OutMontageThirdPerson = nullptr;

	if (!Table)
		return;

	FSAnimation* findAnim = Table->FindRow<FSAnimation>(Name, "");
	if (!findAnim)
		return;

	OutIsValid = true;
	if(OutMontageFirstPerson)
		*OutMontageFirstPerson = findAnim->SequenceBaseFirstPerson;
	if(OutMontageThirdPerson)
		*OutMontageThirdPerson = findAnim->SequenceBaseThirdPerson;
}

USkeletalMeshComponent* USC_Inventory::GetCharacterMesh()
{
	if (FirstPersonMesh)
		return FirstPersonMesh;

	IIInventoryTarget* inventoryTargetItf = Cast<IIInventoryTarget>(GetPawnOwner());
	FirstPersonMesh = inventoryTargetItf->GetViewmodelArms();

	verifyf(FirstPersonMesh, TEXT("invalid first person mesh arms"));

	return FirstPersonMesh;
}

void USC_Inventory::EventSetFullyHolstered(bool InFullyHolstered)
{
	if (!InFullyHolstered)
		FullyHolstered = false;

	switch (HolsterState)
	{
		case EWeaponHolsterState::Available:
		break;
		case EWeaponHolsterState::Holstered:
			FullyHolstered = true;
		break;
	}
}

void USC_Inventory::EventServerTryDropEquipped()
{
	TryDropEquipped(false);
}

void USC_Inventory::TryDropEquipped(bool PlayDropAnimation)
{
	if (!bCanDropItems)
		return;

	if (Inventory.Num() > 1)
	{
		DropEquipped();
	}
}

void USC_Inventory::DropEquipped()
{
	Inventory.Remove(GetEquipped());

	StopAllOwnerMontage();


    IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());

    UCameraComponent* cameraComp = Helpers::GetComponent<UCameraComponent>(GetPawnOwner());
    weaponItf->OnWeaponDrop(cameraComp->GetForwardVector() * DroppingForce, cameraComp->GetForwardVector() * DroppingForceAngular);

    GetEquipped()->SetOwner(nullptr);
    weaponItf->OnUnequipped();

    SetEquippedItem(nullptr);
}

void USC_Inventory::StopAllOwnerMontage()
{
    IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());

	verifyf(weaponItf, TEXT("invalie equipped item"));
	weaponItf->OnMontageStopAll(0.f);
	weaponItf->OnStopAudioPlaying();

	GetCharacterMesh()->GetAnimInstance()->Montage_Stop(0.f);

}

void USC_Inventory::EventServerTryEquipItemAdded(int32 Added)
{
	TryEquipItemAdded(Added);
}

void USC_Inventory::TryEquipItemAdded(int32 Added)
{
	NextAdded = GetEquippedIndex() + Added;
	if (Inventory.Num() > NextAdded)
	{
		EventTryEquipItem(0, true);
	}
	else
	{
		if (NextAdded > 0)
		{
			EventTryEquipItem(Inventory.Num() - 1, true);
		}
		else
		{
            EventTryEquipItem(NextAdded, true);
		}
	}
}

int32 USC_Inventory::GetEquippedIndex()
{
	return Inventory.Find(GetEquipped());
}

void USC_Inventory::EventServerTryEquipItem(int32 ItemIndex)
{
	EventTryEquipItem(ItemIndex, true);
}

void USC_Inventory::EventServerTryEquipNextItem()
{
	EventTryEquipItem(GetNextItemIndex(), true);
}

int32 USC_Inventory::GetNextItemIndex()
{
	if (GetEquippedIndex() + 1 > Inventory.Num() - 1)
	{
		return 0;
	}
	return GetEquippedIndex() + 1;
}

void USC_Inventory::EventServerTryEquipPrevItem()
{
	EventTryEquipItem(GetPrevItemIndex(), true);
}

int32 USC_Inventory::GetPrevItemIndex()
{
    if (GetEquippedIndex() - 1 > Inventory.Num() - 1)
    {
        return 0;
    }
    return GetEquippedIndex() - 1;
}

void USC_Inventory::EventServerUnholster()
{
	EventServerUnholsterWithName(GetNameMontageUnholster());
}

FName USC_Inventory::GetNameMontageUnholster()
{
	return GetCharacterMesh()->GetAnimInstance()->IsAnyMontagePlaying() && !FullyHolstered ? "Unholster-Smooth" : "Unholster";
}

void USC_Inventory::EventTryEquipItem(int32 Index, bool bHolster)
{
	bEquippingHolster = bHolster;
	EquippingItem = Index;
	EventTryEquipItemCore();
}

void USC_Inventory::EventTryEquipItemCore()
{
	if (GetHolsterState() != EWeaponHolsterState::Holstered)
	{
		if (GetEquippedIndex() != EquippingItem)
		{
			return;
		}
	}

	if (!Inventory.IsValidIndex(EquippingItem))
		return;

	IICharacter* charItf = Cast<IICharacter>(GetPawnOwner());
	verifyf(charItf, TEXT("invalid character"));

	if (!charItf->TryStartAbility(SwappingAbility))
		return;

	if ((GetHolsterState() == EWeaponHolsterState::Available) && bEquippingHolster)
	{
		HolsterState = EWeaponHolsterState::Holstered;

		EventMulticastHolster();

		while (!FullyHolstered)
		{
			UKismetSystemLibrary::RetriggerableDelay(GetWorld(), 0.05f, FLatentActionInfo());
		}
	}

	IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());

	static UDataTable* physicsDT;
	if(!physicsDT)
        Helpers::GetAssetDynamic(&physicsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));

	FDataTableRowHandle rowHandle;
	rowHandle.DataTable = physicsDT;
	rowHandle.RowName = TEXT("Hidden");
	weaponItf->OnChangeSettingsPhysical(rowHandle);

	weaponItf->OnUnequipped();

	EquipItem(Inventory[EquippingItem]);

	SetRefreshUnholster(!bRefreshUnholster);
}


EWeaponHolsterState USC_Inventory::GetHolsterState()
{
	return HolsterState;
}

void USC_Inventory::EventMulticastHolster()
{
	EventHolster();
}

void USC_Inventory::SetRefreshUnholster(bool InRefreshUnholster)
{
	bRefreshUnholster = InRefreshUnholster;

	UnholsterName = TEXT("Unholster");
	HolsterState = EWeaponHolsterState::Available;
	EventUnholster();
}

void USC_Inventory::EventHolster()
{
	EventHolsterCore();
}

void USC_Inventory::EventHolsterCore()
{
	HolsterName = GetNameMontageHolster();

	IIWeapon* weaponItf = Cast<IIWeapon>(GetEquipped());
	verifyf(weaponItf, TEXT("invalid weapon"));

	bool bValid;

	UAnimMontage* montageFirstPerson;

	GetAnimationMontagefromDataTable(weaponItf->GetCharacterAnimationMontages(), HolsterName, bValid, &montageFirstPerson, nullptr);

	if (OnHolstering.IsBound())
		OnHolstering.Broadcast();

	GetCharacterMesh()->GetAnimInstance()->Montage_Play(montageFirstPerson);

	EventSetFullyHolstered(false);

	weaponItf->OnMontagePlay(HolsterName, true);
}

FName USC_Inventory::GetNameMontageHolster()
{
	return GetCharacterMesh()->GetAnimInstance()->IsAnyMontagePlaying() ? TEXT("Holster") : TEXT("Holster-Smooth");
}

void USC_Inventory::EventServerTryPickupItem(AActor* Item)
{
	TryPickUpItem(Item);
}

void USC_Inventory::TryPickUpItem(AActor* Item)
{
	if (!HasSpace())
	{
		TryDropEquipped(false);
	}

	Inventory.AddUnique(Item);

	IIWeapon* weaponItf = Cast<IIWeapon>(Item);


    FDataTableRowHandle physicsRowHandle;
    static UDataTable* physicsDT;
    if (!physicsDT)
        Helpers::GetAssetDynamic(&physicsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));
    physicsRowHandle.DataTable = physicsDT;
    physicsRowHandle.RowName = TEXT("Hidden");

	weaponItf->OnChangeSettingsPhysical(physicsRowHandle);

	Item->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	IIInteractable* interactable = Cast<IIInteractable>(Item);
	interactable->OnSetCanInteract(false);

	Item->SetOwner(GetPawnOwner());

	StopAllOwnerMontage();

	EventTryEquipItem(Inventory.Num() - 1, false);
}

bool USC_Inventory::HasSpace()
{
	return Inventory.Num() < InventoryCapacity;
}

