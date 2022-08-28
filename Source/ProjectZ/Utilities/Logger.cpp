#include "Logger.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(GameProject, Display, All)

void Logger::Print(int32 InValue, int32 InKey, float InDuration, FColor InColor)
{
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
}

void Logger::Print(float InValue, int32 InKey, float InDuration, FColor InColor)
{
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
}

void Logger::Print(const FString& InValue, int32 InKey, float InDuration, FColor InColor)
{
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
}

void Logger::Print(const FVector& InValue, int32 InKey, float InDuration, FColor InColor)
{
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void Logger::Print(const FRotator& InValue, int32 InKey, float InDuration, FColor InColor)
{
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void Logger::Log(int32 InValue)
{
    UE_LOG(GameProject, Display, L"%d", InValue);
}

void Logger::Log(float InValue)
{
    UE_LOG(GameProject, Display, L"%f", InValue);
}

void Logger::Log(const FString& InValue)
{
    UE_LOG(GameProject, Display, L"%s", *InValue);
}

void Logger::Log(const FVector& InValue)
{
    UE_LOG(GameProject, Display, L"%s", *InValue.ToString());
}

void Logger::Log(const FRotator& InValue)
{
    UE_LOG(GameProject, Display, L"%s", *InValue.ToString());
}

void Logger::Log(const UObject* InObject)
{
    FString str;

    if (!!InObject)
        str.Append(InObject->GetName());

    str.Append(!!InObject ? " Not Null" : "Null");

    UE_LOG(GameProject, Display, L"%s", *str);
}

void Logger::Log(const FString& InFuncName, int32 InLineNumber)
{
    FString str;
    str.Append(InFuncName);
    str.Append(", ");
    str.Append(FString::FromInt(InLineNumber));

    UE_LOG(GameProject, Display, L"%s", *str);
}

