﻿
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ModioModule.h"
#include "Modio.h"
#include "Core.h"
#include "Engine/Engine.h"
#include "Logging/LogVerbosity.h"
#include "ModioSDK.h"
#include "ModioSettings.h"

#if WITH_EDITOR
	#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "FModioModule"

void FModioModule::StartupModule()
{
	Modio::SetLogCallback([](Modio::LogLevel Level, std::string Message) {
		UE_LOG(LogModio, Log, TEXT("%s"), UTF8_TO_TCHAR(Message.c_str()));
	});

	RegisterSettings();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
	// file per-module

	// Get the base directory of this plugin
	// FString BaseDir = IPluginManager::Get().FindPlugin("modio")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	// FString LibraryPath;
	/*#if PLATFORM_WINDOWS
		LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/modioLibrary/Win64/ExampleLibrary.dll"));
	#elif PLATFORM_MAC
		LibraryPath = FPaths::Combine(*BaseDir,
	TEXT("Source/ThirdParty/modioLibrary/Mac/Release/libExampleLibrary.dylib")); #endif // PLATFORM_WINDOWS

		ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

		if (ExampleLibraryHandle)
		{
			// Call the test function in the third party library that opens a message box
			ExampleLibraryFunction();
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party
	library"));
		}*/
}

void FModioModule::UnregisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "mod.io");
	}
#endif // WITH_EDITOR
}

void FModioModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "mod.io", LOCTEXT("RuntimeSettingsName", "mod.io"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the mod.io plugin"),
										 GetMutableDefault<UModioSettings>());
	}
#endif
}

void FModioModule::ShutdownModule()
{
	UnregisterSettings();
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	//	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	//	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FModioModule, Modio)
