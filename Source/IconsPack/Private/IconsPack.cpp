// Copyright 2024 Steven Barsam All rights reserved.

#include "IconsPack.h"
#include "UObject/NoExportTypes.h"

#if WITH_EDITOR
#include "Modules/ModuleManager.h"
#include "Factories/FontFactory.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "UObject/SavePackage.h"
#include "Interfaces/IPluginManager.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#endif

#define LOCTEXT_NAMESPACE "FIconsPackModule"

void FIconsPackModule::StartupModule()
{
    #if WITH_EDITOR
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    if (GIsEditor)
    {
        FCoreDelegates::OnPostEngineInit.AddLambda([this]()
            {
                FString PluginBaseDir = IPluginManager::Get().FindPlugin("IconsPack")->GetBaseDir();

                IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
                FString FontFolderPath = FPaths::Combine(PluginBaseDir, TEXT("/Content/IconsPack/Fonts/"));
                if (PlatformFile.DirectoryExists(*FontFolderPath)) {
                    // If the directory exists, we can assume setup has been run
                    return;
                }

                TArray<FString> FontArray = { TEXT("GoogleSymbols100"), TEXT("GoogleSymbols200"), TEXT("GoogleSymbols300"), TEXT("GoogleSymbols400"), TEXT("GoogleSymbols500"), TEXT("GoogleSymbols600"), TEXT("GoogleSymbols700"), TEXT("GoogleSymbols100Fill"), TEXT("GoogleSymbols200Fill"), TEXT("GoogleSymbols300Fill"), TEXT("GoogleSymbols400Fill"), TEXT("GoogleSymbols500Fill"), TEXT("GoogleSymbols600Fill"), TEXT("GoogleSymbols700Fill") };
                for (const FString& FontName : FontArray)
                {
                    CreateFontAssetsFromTTF(FontName);
                }
            });
    }
    #endif
}

void FIconsPackModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

/*
Fab Marketplace requires all Third Party assets be placed in the Source folder, not in Content
This means that we have to provide the raw TTF files, then convert them to .uassets on initial launch
*/
void FIconsPackModule::CreateFontAssetsFromTTF(const FString& FontName)
{
    #if WITH_EDITOR

    FString PluginBaseDir = IPluginManager::Get().FindPlugin("IconsPack")->GetBaseDir();

    // Path to your TTF file located in the plugin's ThirdParty folder
    FString TTFName = TEXT("Source/ThirdParty/") + FontName + TEXT(".ttf");
    FString TTFFilePath = FPaths::Combine(PluginBaseDir, TTFName);
    FString FontAssetPath = TEXT("/IconsPack/IconsPack/Fonts/") + FontName;
    FString FontFaceName = FontName + "Face";
    FString FontFaceAssetPath = TEXT("/IconsPack/IconsPack/FontFaces/") + FontFaceName;

    // Initialize the Asset Tools module to create assets
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

    // Create a new package for the font asset
    UPackage* Package = CreatePackage(*FontFaceAssetPath);
    if (!Package)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create package for font asset."));
        return;
    }

    // Create a FontFace object
    UFontFace* FontFace = NewObject<UFontFace>(Package, *FontFaceName, RF_Public | RF_Standalone);

    // Set the TTF file path for the FontFace
    FontFace->SourceFilename = TTFFilePath;
    FontFace->Hinting = EFontHinting::Default;
    FontFace->LoadingPolicy = EFontLoadingPolicy::LazyLoad;

    // Mark the package as dirty to ensure it's saved
    Package->MarkPackageDirty();

    // Save the package as a .uasset file
    FString PackageFileName = FPackageName::LongPackageNameToFilename(FontFaceAssetPath, FPackageName::GetAssetPackageExtension());
    FSavePackageArgs SaveArgs;
    SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
    if (UPackage::SavePackage(Package, FontFace, *PackageFileName, SaveArgs))
    {
        UE_LOG(LogTemp, Log, TEXT("FontFace asset saved successfully at: %s"), *PackageFileName);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save FontFace asset."));
    }

    // With the FontFace created, make the Font
    UPackage* FontPackage = CreatePackage(*FontAssetPath);
    if (!FontPackage)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create package for font asset."));
        return;
    }

    UFont* NewFont = NewObject<UFont>(FontPackage, UFont::StaticClass(), *FontName, RF_Public | RF_Standalone);
    if (!NewFont)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create UFont."));
        return;
    }

    FCompositeFont CompositeFont(
        FName("Regular"),         
        FontFace->SourceFilename,             
        EFontHinting::Default,  
        EFontLoadingPolicy::LazyLoad  
    );
    NewFont->FontCacheType = EFontCacheType::Runtime;
    NewFont->CompositeFont = CompositeFont;
    NewFont->LegacyFontSize = 24;
    NewFont->LegacyFontName = "Regular";

    FAssetRegistryModule::AssetCreated(NewFont);
    FontPackage->MarkPackageDirty();

    FString FontPackageFileName = FPackageName::LongPackageNameToFilename(FontAssetPath, FPackageName::GetAssetPackageExtension());

    if (!UPackage::SavePackage(FontPackage, NewFont, *FontPackageFileName, SaveArgs))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save UFont asset as UAsset."));
        return;
    }
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIconsPackModule, IconsPack)