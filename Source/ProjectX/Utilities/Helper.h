#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

class PROJECTX_API Helpers
{
public:
    template<typename T>
    static void GetAsset(T** OutObject, FString InPath)
    {
        ConstructorHelpers::FObjectFinder<T> asset(*InPath);
        verifyf(asset.Succeeded(), L"Asset Object Not Found");

        *OutObject = asset.Object;
    }

    template<typename T>
    static void GetAssetDynamic(T** OutObject, FString InPath)
    {
        T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
        verifyf(!!obj, L"Asset Object Not Found");

        *OutObject = obj;
    }

    template<typename T>
    static void GetClass(TSubclassOf<T>* OutObject, FString InPath)
    {
        ConstructorHelpers::FClassFinder<T> asset(*InPath);
        verifyf(asset.Succeeded(), L"Asset Class Not Found");

        *OutObject = asset.Class;
    }

    template<typename T>
    static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr, FName InSocketName = FName(TEXT("")))
    {
        *OutComponent = InActor->CreateDefaultSubobject<T>(InName);

        if (!!InParent)
        {
            (*OutComponent)->SetupAttachment(InParent, InSocketName);
            return;
        }

        InActor->SetRootComponent(*OutComponent);
    }


    template<typename T>
    static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
    {
        *OutComponent = InActor->CreateDefaultSubobject<T>(InName);
    }

    template<typename T>
    static T* GetComponent(AActor* InActor)
    {
        return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
    }

    static void DrawGizmo(USceneComponent* InSceneComponent)
    {
        DrawDebugDirectionalArrow(InSceneComponent->GetWorld(), InSceneComponent->GetComponentLocation(), InSceneComponent->GetComponentLocation() + (InSceneComponent->GetForwardVector() * 15.f), 5.f, FColor::Red, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InSceneComponent->GetWorld(), InSceneComponent->GetComponentLocation(), InSceneComponent->GetComponentLocation() + (InSceneComponent->GetUpVector() * 15.f), 5.f, FColor::Blue, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InSceneComponent->GetWorld(), InSceneComponent->GetComponentLocation(), InSceneComponent->GetComponentLocation() + (InSceneComponent->GetRightVector() * 15.f), 5.f, FColor::Green, false, 0.1f, 0.f, 1.f);
    }

    static void DrawGizmo(UWorld* InWorld, FTransform InTransform)
    {
        DrawDebugDirectionalArrow(InWorld, InTransform.GetLocation(), InTransform.GetLocation() + (InTransform.GetRotation().GetForwardVector() * 15.f), 5.f, FColor::Red, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InWorld, InTransform.GetLocation(), InTransform.GetLocation() + (InTransform.GetRotation().GetUpVector() * 15.f), 5.f, FColor::Blue, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InWorld, InTransform.GetLocation(), InTransform.GetLocation() + (InTransform.GetRotation().GetRightVector() * 15.f), 5.f, FColor::Green, false, 0.1f, 0.f, 1.f);
    }

    static void DrawGizmo(UWorld* InWorld, FVector InLocation, FQuat InQuat)
    {
        DrawDebugDirectionalArrow(InWorld, InLocation, InLocation + (InQuat.GetForwardVector() * 15.f), 5.f, FColor::Red, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InWorld, InLocation, InLocation + (InQuat.GetUpVector() * 15.f), 5.f, FColor::Blue, false, 0.1f, 0.f, 1.f);
        DrawDebugDirectionalArrow(InWorld, InLocation, InLocation + (InQuat.GetRightVector() * 15.f), 5.f, FColor::Green, false, 0.1f, 0.f, 1.f);
    }
};