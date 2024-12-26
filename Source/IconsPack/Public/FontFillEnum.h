#pragma once

#include "CoreMinimal.h"
#include "FontFillEnum.generated.h"

UENUM(BlueprintType)
enum class EFontFillEnum : uint8
{
    NoFill UMETA(DisplayName = "No Fill"),
    Fill UMETA(DisplayName = "Fill"),
};