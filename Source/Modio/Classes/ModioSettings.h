﻿#pragma once

#include "Types/ModioCommonTypes.h"

#include "ModioSettings.generated.h"

/** @brief Settings that can be configured per project that generally don't change during the run of a game */
UCLASS(Config = Game, defaultconfig)
class UModioSettings : public UObject
{
	GENERATED_BODY()
public:
	UModioSettings();

	/** Game id that can be found in your game configuration page on the mod.io site. Unique per environment  */
	UPROPERTY(EditDefaultsOnly, config, Category = "Project")
	int64 GameId;

	/** ApiKey that can be found in your game configuration page on the mod.io site. Unique per environment  */
	UPROPERTY(EditDefaultsOnly, config, Category = "Project")
	FString ApiKey;

	/** If your game is configured to be running on either mod.io or test.mod.io. Recommended is to first create your
	 * game on test.mod.io as only you and your team can see it there */
	UPROPERTY(EditDefaultsOnly, config, Category = "Project")
	EModioEnvironment Environment = EModioEnvironment::Test;

	/** What's the default log level you are interested in */
	UPROPERTY(EditDefaultsOnly, config, Category = "Project")
	EModioLogLevel LogLevel;

	/** The default portal to use.*/
	UPROPERTY(EditDefaultsOnly, config, Category = "Project")
	EModioPortal DefaultPortal = EModioPortal::None;

private:
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
