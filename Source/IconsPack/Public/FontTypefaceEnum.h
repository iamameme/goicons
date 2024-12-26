#pragma once

#include "CoreMinimal.h"
#include "FontTypefaceEnum.generated.h"

UENUM(BlueprintType)
enum class EFontTypefaceEnum : uint8
{
    Thin UMETA(DisplayName = "Thin"),
    ExtraLight UMETA(DisplayName = "Extra Light"),
    Light UMETA(DisplayName = "Light"),
    Regular UMETA(DisplayName = "Regular"),
    Medium UMETA(DisplayName = "Medium"),
    SemiBold UMETA(DisplayName = "Semi-Bold"),
    Bold UMETA(DisplayName = "Bold"),
};