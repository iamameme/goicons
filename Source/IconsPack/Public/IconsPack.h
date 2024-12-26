// Copyright 2024 Steven Barsam All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class FIconsPackModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void CreateFontAssetsFromTTF(const FString& FontName);
};
