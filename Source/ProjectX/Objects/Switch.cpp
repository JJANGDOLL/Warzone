// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Switch.h"
#include "Utilities/Global.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Base, TEXT("Base"));
    Helpers::CreateComponent(this, &Button, TEXT("Button"), Base);

	Base->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.03f));
    
	UStaticMesh* cube;
	Helpers::GetAsset(&cube, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	Base->SetStaticMesh(cube);

    UStaticMesh* btn;
    Helpers::GetAsset(&btn, TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Button->SetStaticMesh(btn);
	Button->AddRelativeLocation(FVector(0.f, 0.f, 25.f));
	Button->SetRelativeScale3D(FVector(0.6f, 0.6f, 1.f));

	UMaterialInstanceConstant* baseMat;
	Helpers::GetAsset(&baseMat, TEXT("MaterialInstanceConstant'/Game/StarterContent/Materials/M_Wood_Oak_Inst.M_Wood_Oak_Inst'"));
	Base->SetMaterial(0, baseMat);

    UMaterialInstanceConstant* btnMat;
    Helpers::GetAsset(&btnMat, TEXT("MaterialInstanceConstant'/Game/Materials/VertexColorViewMode_RedOnly_Inst.VertexColorViewMode_RedOnly_Inst'"));
	Button->SetMaterial(0, btnMat);
}

void ASwitch::Action()
{
	if (!Target)
		return;

	bDir = !bDir;
}

void ASwitch::PostInitializeComponents()
{
    Super::PostInitializeComponents();

	if (!Target)
		return;

	Forward = Target->GetActorLocation();
	Backward = Target->GetActorLocation();

	Backward += FVector(-1500.f, 0.f, 0.f);
}

void ASwitch::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (!Target)
		return;

	if (bDir)
	{
		Target->SetActorLocation(FMath::VInterpTo(Target->GetActorLocation(), Backward, DeltaSeconds, 1.f));
	}
	else
	{
		Target->SetActorLocation(FMath::VInterpTo(Target->GetActorLocation(), Forward, DeltaSeconds, 1.f));
	}
}

FText ASwitch::Description()
{
	return FText::FromString(TEXT("Toggle target"));
}

