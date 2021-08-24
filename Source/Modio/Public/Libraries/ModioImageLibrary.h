﻿#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/ModioCommonTypes.h"
#include "Types/ModioImage.h"
#include "Types/ModioImageState.h"

// clang-format off
#include "ModioImageLibrary.generated.h"
// clang-format on

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLoadImageDelegate, class UTexture2DDynamic*, Texture);

UCLASS()
class UModioImageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Get the texture if if has been loaded by any FModioImage instance */
	UFUNCTION(BlueprintPure, Category = "mod.io|Image")
	static class UTexture2DDynamic* GetTexture(const FModioImage& Image);

	/** Load the texture into memory async, if it's already in memory, then we will return immediately */
	UFUNCTION(BlueprintCallable, Category = "mod.io|Image")
	static void LoadAsync(const FModioImage& Image, FOnLoadImageDelegate OnImageLoaded);

	/** Get the current state of the image */
	UFUNCTION(BlueprintPure, Category = "mod.io|Image")
	static EModioImageState GetState(const FModioImage& Image);

	/**
	 * If a logo size is EModioLogoSize::Original, then the size of the Logo returned,
	 * else, the thumbnail size a logo is returned
	 * @param Logo If null and EModioLogoSize::Original is passed, then (0, 0) is returned
	 * @param LogoSize The size of the logo we want to return
	 *
	 * @return Dimensions of the logo if displayed in a 1:1 pixel ratio
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Image")
	static FVector2D GetLogoSize(class UTexture* Logo, EModioLogoSize LogoSize);
	
	/**
	 * If a avatar size is EModioAvatarSize::Original, then the size of the Logo returned,
	 * else, the thumbnail size a avatar is returned
	 * @param Avatar If null and EModioAvatarSize::Original is passed, then (0, 0) is returned
	 * @param AvatarSize The size of the avatar we want to return
	 *
	 * @return Dimensions of the avatar if displayed in a 1:1 pixel ratio
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Image")
	static FVector2D GetAvatarSize(class UTexture* Avatar, EModioAvatarSize AvatarSize);

	/**
	 * If a gallery image size is EModioGallerySize::Original, then the size of the gallery image returned,
	 * else, the thumbnail size a gallery image is returned
	 * @param GalleryImage If null and EModioGallerySize::Original is passed, then (0, 0) is returned
	 * @param GallerySize The size of the gallery image we want to return
	 *
	 * @return Dimensions of the gallery image if displayed in a 1:1 pixel ratio
	 */
	UFUNCTION(BlueprintPure, Category = "mod.io|Image")
	static FVector2D GetGallerySize(class UTexture* GalleryImage, EModioGallerySize GallerySize);
};
