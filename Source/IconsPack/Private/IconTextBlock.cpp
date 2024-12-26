// Copyright 2024 Steven Barsam All rights reserved.

#include "IconTextBlock.h"
#include "Engine/DataTable.h"

UIconTextBlock::UIconTextBlock(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) // Call the base class constructor
{
    FString DataTablePath = TEXT("/IconsPack/IconsPack/DataTables/GoogleSymbolsIconTable");

    UDataTable* GlyphDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));

    GlyphOptions.Empty();

    if (GlyphDataTable)
    {
        static const FString ContextString(TEXT("Dropdown Options"));
        TArray<FIconDataTableRow*> Rows;
        GlyphDataTable->GetAllRows(ContextString, Rows);

        SelectedGlyph = Rows[0]->Name;

        for (const FIconDataTableRow* Row : Rows)
        {
            GlyphOptions.Add(Row->Name);
            GlyphIDs.Add(Row->ID);
        }

        HandleEnumChange();
    }
}

void UIconTextBlock::SetSelectedGlyph(FString NewGlyph) {
    SelectedGlyph = NewGlyph;
    HandleEnumChange();
}

void UIconTextBlock::SetFill(bool NewFill) {
    FontFillOption = NewFill;
    HandleEnumChange();
}

void UIconTextBlock::SetTypeface(EFontTypefaceEnum NewTypeface) {
    FontTypefaceOption = NewTypeface;
    HandleEnumChange();
}

TArray<FString> UIconTextBlock::GetDropdownOptions() const
{
    return GlyphOptions;
}


void UIconTextBlock::HandleEnumChange()
{
    FString FontAsset;
    if (FontFillOption) {
        switch (FontTypefaceOption)
        {
        case EFontTypefaceEnum::Thin:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols100Fill");
            break;

        case EFontTypefaceEnum::ExtraLight:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols200Fill");
            break;

        case EFontTypefaceEnum::Light:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols300Fill");
            break;

        case EFontTypefaceEnum::Regular:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols400Fill");
            break;

        case EFontTypefaceEnum::Medium:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols500Fill");
            break;

        case EFontTypefaceEnum::SemiBold:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols600Fill");
            break;

        case EFontTypefaceEnum::Bold:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols700Fill");
            break;

        default:
            break;
        }
    }
    else {
        switch (FontTypefaceOption)
        {
        case EFontTypefaceEnum::Thin:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols100");
            break;

        case EFontTypefaceEnum::ExtraLight:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols200");
            break;

        case EFontTypefaceEnum::Light:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols300");
            break;

        case EFontTypefaceEnum::Regular:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols400");
            break;

        case EFontTypefaceEnum::Medium:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols500");
            break;

        case EFontTypefaceEnum::SemiBold:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols600");
            break;

        case EFontTypefaceEnum::Bold:
            FontAsset = TEXT("/IconsPack/IconsPack/Fonts/GoogleSymbols700");
            break;

        default:
            break;
        }
    }

    const FSlateFontInfo& CurrentFont = GetFont();
    UObject* LoadedFont = LoadObject<UObject>(nullptr, *FontAsset);
    if (LoadedFont)
    {
        // Create FSlateFontInfo using the loaded font and specified size
        FSlateFontInfo FontInfo(LoadedFont, CurrentFont.Size);
        // Preserve the existing font material
        UObject* ExistingFontMaterial = CurrentFont.FontMaterial;
        FontInfo.FontMaterial = ExistingFontMaterial;
        FontInfo.OutlineSettings = CurrentFont.OutlineSettings;
        FontInfo.LetterSpacing = CurrentFont.LetterSpacing;
        FontInfo.SkewAmount = CurrentFont.SkewAmount;

        // Set the font on the TextBlock
        SetFont(FontInfo);
    }

    // Set icon as text
    int32 Index = GlyphOptions.Find(SelectedGlyph);
    if (GlyphIDs.IsValidIndex(Index)) {
        int32 UnicodeCodePoint = GlyphIDs[Index];  // 0xE000; //57344; //GlyphIDs[Index];

        // Convert the Unicode code point to a UTF-16 character
        TCHAR UnicodeCharacter = (TCHAR)UnicodeCodePoint;

        // Create a FString to represent the character
        FString CharacterString = FString(1, &UnicodeCharacter);

        // Convert the FString to FText
        FText UnicodeText = FText::FromString(CharacterString);
        SetText(UnicodeText);
    }
}

#if WITH_EDITOR
void UIconTextBlock::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    HandleEnumChange();
}
#endif