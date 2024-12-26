// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Text3DActor.h"
#include "FontTypefaceEnum.h"
#include "FontFillEnum.h"
#include "IconDataTableRow.h"
#include "Engine/TextRenderActor.h"
#include "IconText3DActor.generated.h"

/**
 * 
 */
UCLASS()
class ICONSPACK_API AIconText3DActor : public AText3DActor
{
	GENERATED_BODY()

public:
	AIconText3DActor();

	UFUNCTION()
	TArray<FString> GetDropdownOptions() const;

	UFUNCTION(BlueprintCallable, Category = "IconPack")
		void SetSelectedGlyph(FString NewGlyph);

	UFUNCTION(BlueprintCallable, Category = "IconPack")
		void SetFill(bool NewFill);

	UFUNCTION(BlueprintCallable, Category = "IconPack")
		void SetTypeface(EFontTypefaceEnum NewTypeface);

protected:
	// The enum property is private, accessed via getter/setter
	UPROPERTY(EditAnywhere, Category = "IconPack", DisplayName = "Fill")
		bool FontFillOption;
	UPROPERTY(EditAnywhere, Category = "IconPack", DisplayName = "Typeface")
		EFontTypefaceEnum FontTypefaceOption;
	// Override NativeConstruct to set up widget elements when it's created

	// Override PostEditChangeProperty to listen for changes in the editor
	#if WITH_EDITORONLY_DATA
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

	// Array of options for the dropdown 
	UPROPERTY(EditAnywhere, Category = "IconPack", meta = (GetOptions = "GetDropdownOptions"))
		FString SelectedGlyph;

	TArray<FString> GlyphOptions;
	TArray<int32> GlyphIDs;

private:
	void HandleEnumChange();
};
