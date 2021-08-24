﻿#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/ModioErrorCode.h"

// clang-format off
#include "ModioErrorCodeLibrary.generated.h"
// clang-format on

UCLASS()
class UModioErrorCodeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Checks if a error code contains a error
	 * @param Error -
	 * @return true if the error code is a error
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Utilities|Error", meta = (CompactNodeTitle = "Error", BlueprintAutocast))
	static bool IsError(const FModioErrorCode& Error);

	/**
	 * Get underlying error code 
	 * @param Error -
	 * @return 0 if there is no error
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Utilities|Error")
	static int32 GetValue(const FModioErrorCode& Error);

	/**
	 * Get the textual representation of the error
	 * @param Error -
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Utilities|Error")
	static FString GetMessage(const FModioErrorCode& Error);
};
