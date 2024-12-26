#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "IconDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FIconDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Example data fields
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
        FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
        int32 ID;

    // Constructor (optional)
    FIconDataTableRow()
        : Name(TEXT("Default Icon")), ID(0xE003)
    {
    }
};