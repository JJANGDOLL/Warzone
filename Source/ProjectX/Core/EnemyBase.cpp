// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/EnemyBase.h"
#include "Engine/SkeletalMesh.h"
#include "Utilities/Global.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Widget/EnemyStatus.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Objects/DamageText.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &StatusWidgetComp, TEXT("StatusWidget"), GetCapsuleComponent());

	USkeletalMesh* skelMesh;
	Helpers::GetAsset(&skelMesh, TEXT("SkeletalMesh'/Game/BSP_ZombieAnims/EpicAssets/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	GetMesh()->SetSkeletalMesh(skelMesh);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	TSubclassOf<UUserWidget> statusWidgetClass;
	Helpers::GetClass(&statusWidgetClass, TEXT("WidgetBlueprint'/Game/ProjectX/Widgets/WBP_EnemyStatus.WBP_EnemyStatus_C'"));

	StatusWidgetComp->SetWidgetClass(statusWidgetClass);
	StatusWidgetComp->AddRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 15.f));
	StatusWidgetComp->SetWidgetSpace(EWidgetSpace::World);    
	StatusWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 	StatusWidget = Cast<UEnemyStatus>(StatusWidgetComp->GetWidget());

	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionProfileName(TEXT("Body"));

	// AnimBlueprint'/Game/ProjectX/Characters/ABP_EnemyBase.ABP_EnemyBase'
    TSubclassOf<UAnimInstance> enemyAnimInst;
    Helpers::GetClass(&enemyAnimInst, TEXT("AnimBlueprint'/Game/ProjectX/Characters/ABP_EnemyBase.ABP_EnemyBase_C'"));
    GetMesh()->SetAnimClass(enemyAnimInst);

	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	
	Helpers::GetAsset(&EnemyBehaviorTree, TEXT("BehaviorTree'/Game/ProjectX/Enemy/BT_Enemy.BT_Enemy'"));

	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyBase::Hitted(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyBase::EnableRun()
{
	PrintLine();

	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

float AEnemyBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth = FMath::Clamp<float>(CurrentHealth - damage, 0, MaxHealth);
	StatusWidget->SetHealth(MaxHealth, CurrentHealth);

	return damage;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
//     AEnemyController* controller = GetWorld()->SpawnActor<AEnemyController>(AEnemyController::StaticClass(), GetActorTransform());

//     PossessedBy(controller);

    StatusWidget = Cast<UEnemyStatus>(StatusWidgetComp->GetWidget());

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter)
	{
		FRotator widgetRot = PlayerCharacter->GetCapsuleComponent()->GetForwardVector().Rotation() * -1;
		FVector dirChar = GetActorLocation() - PlayerCharacter->GetActorLocation();

		dirChar.Normalize();
		if ( FVector::DotProduct(PlayerCharacter->GetCapsuleComponent()->GetForwardVector(), dirChar) > 0.995f)
		{
			StatusWidgetComp->SetVisibility(true);
			StatusWidgetComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f) - GetActorRotation());
			StatusWidgetComp->AddRelativeRotation(FRotator(0.f, widgetRot.Yaw * -1.f, 0.f));
		}
		else
		{
            StatusWidgetComp->SetVisibility(false);
		}
	}

// 	auto curPos = GetActorLocation();
// 	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
// 
// 	FVector direction = playerPos - curPos;
// 	direction.Normalize();
// 	SetActorLocation(curPos + direction);

	if (CurrentHealth <= 0)
	{
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
