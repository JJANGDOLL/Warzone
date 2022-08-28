// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugTimeController.h"
#include <Components/InputComponent.h>

#include "Utilities/Global.h"
#include <GameFramework/PlayerInput.h>
#include <Widgets/SWeakWidget.h>
#include "SDebugTimeWidget.h"

// Sets default values
ADebugTimeController::ADebugTimeController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebugTimeController::BeginPlay()
{
	Super::BeginPlay();

    _TimeScaleCurrent = _TimeScaleDefault;

    _bPaused = false;

	BindToInput();

//     // Pass our viewport a weak ptr to our widget
//     // Viewport's weak ptr will not give Viewport ownership of Widget
//     GEngine->GameViewport->AddViewportWidgetContent(
//         SNew(SWeakWidget)
//         .PossiblyNullContent(MyUIWidget.ToSharedRef())
//     );
// 
//     // Set widget's properties as visible (sets child widget's properties recursively)
//     MyUIWidget->SetVisibility(EVisibility::Visible);

    _ui = SNew(SDebugTimeWidget).OwnerActor(this);

    GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(_ui.ToSharedRef()));
    _ui->SetVisibility(EVisibility::Visible);
}

// Called every frame
void ADebugTimeController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), FMath::FInterpTo(UGameplayStatics::GetGlobalTimeDilation(GetWorld()), _TimeScaleCurrent, DeltaTime, 20.0f));
}

void ADebugTimeController::TestFunc()
{
    PrintLine();
}

void ADebugTimeController::BindToInput()
{
    // Initialize our component
    InputComponent = NewObject<UInputComponent>(this);
    InputComponent->RegisterComponent();

    if (InputComponent)
    {
        // Bind inputs here
        // InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
        // etc...

        FInputActionKeyMapping speedUp("Time (Speed Up)", EKeys::Add, 0, 0, 0, 0);
        FInputActionKeyMapping speedDown("Time (Slow Down)", EKeys::Subtract, 0, 0, 0, 0);
        FInputActionKeyMapping freeze("Freeze", EKeys::Multiply, 0, 0, 0, 0);

        GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(speedUp);
        GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(speedDown);
        GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(freeze);

        InputComponent->BindAction("Time (Speed Up)", IE_Pressed, this, &ADebugTimeController::IncreaseTimeSclae);
        InputComponent->BindAction("Time (Slow Down)", IE_Pressed, this, &ADebugTimeController::DecreaseTimeSclae);
        InputComponent->BindAction("Freeze", IE_Pressed, this, &ADebugTimeController::Pause).bExecuteWhenPaused = true;

        // Now hook up our InputComponent to one in a Player
        // Controller, so that input flows down to us
        EnableInput(GetWorld()->GetFirstPlayerController());
    }
}

void ADebugTimeController::IncreaseTimeSclae()
{
    PrintLine();

    UpdateTimeScale(_TimeScaleCurrent + _TimeScaleIncrements);
}

void ADebugTimeController::DecreaseTimeSclae()
{
    PrintLine();

    UpdateTimeScale(_TimeScaleCurrent - _TimeScaleIncrements);
}

void ADebugTimeController::UpdateTimeScale(float InValue)
{
    float clampedTime = FMath::Clamp(InValue, 0.1f, 1.0f);
    if (!FMath::IsNearlyEqual(_TimeScaleCurrent, clampedTime))
    {
        _TimeScaleCurrent = clampedTime;
    }
}

void ADebugTimeController::Pause()
{
    PrintLine();

    _bPaused = !_bPaused;
    UGameplayStatics::SetGamePaused(GetWorld(), _bPaused);
}

float ADebugTimeController::GetTimeScale()
{
    return _TimeScaleCurrent;
}

bool ADebugTimeController::IsPaused()
{
    return _bPaused;
}

