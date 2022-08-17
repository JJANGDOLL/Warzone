// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/SDebugTimeWidget.h"
#include "SlateOptMacros.h"

#include "DebugTimeController.h"
#include "Fonts/SlateFontInfo.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDebugTimeWidget::Construct(const FArguments& InArgs)
{
    OwnerActor = InArgs._OwnerActor;
    _TimeDilation.Bind(this, &SDebugTimeWidget::GetDilation);
    _Paused.Bind(this, &SDebugTimeWidget::IsPaused);
    ChildSlot
    [
        SNew(SOverlay)
        + SOverlay::Slot().Padding(50, 30)
        .HAlign(HAlign_Right)
        .VAlign(VAlign_Top)
        [
            SNew(STextBlock)
            .Text(_TimeDilation)
            .ColorAndOpacity(FSlateColor(FColor::Green))
            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16))
        ]
        + SOverlay::Slot()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            SNew(STextBlock)
            .Text(_Paused)
            .ColorAndOpacity(FSlateColor(FColor::Black))
            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 30))
        ]
    ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SDebugTimeWidget::GetGlobalTimeDilation(const UObject* WorldContextObject)
{
    UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (World != nullptr)
    {
        AWorldSettings* const WorldSettings = World->GetWorldSettings();
        if (WorldSettings != nullptr)
        {
            return WorldSettings->TimeDilation;
        }
    }

    return 0.f;
}

FText SDebugTimeWidget::GetDilation() const
{
    if (OwnerActor == nullptr)
    {
        return FText::FromString(TEXT("Time Dilation : --"));
    }
    
    FString head = TEXT("Time Dilation : ");
    FString dil = FString::SanitizeFloat(OwnerActor->GetTimeScale());
    head += dil;

    return FText::FromString(head);
}

FText SDebugTimeWidget::IsPaused() const
{
    if (OwnerActor == nullptr)
    {
        return FText::FromString(TEXT("Actor Error!!"));
    }
    bool bPause = OwnerActor->IsPaused();
    if (bPause)
    {
        return FText::FromString("PAUSE");
    }
    return FText::FromString("");
}

