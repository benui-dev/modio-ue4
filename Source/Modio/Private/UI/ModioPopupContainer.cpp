﻿#include "UI/ModioPopupContainer.h"
#include "UI/ModioPopupBase.h"

UModioPopupContainer::UModioPopupContainer(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
	Visibility = ESlateVisibility::Collapsed;
}

UModioPopupBase* UModioPopupContainer::PushPopup_Implementation(TSubclassOf<UModioPopupBase> PopupClass)
{
	if (!IsValid(PopupClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("Null popup provided to %s::PushPopup"), *GetName())
		return nullptr;
	}
	
	UModioPopupBase** CachedPopup =
		PopupCache.FindByPredicate([PopupClass](UModioPopupBase* Popup) { return Popup->IsA(PopupClass); });

	// Ensure that we are visible
	SetVisibility(ESlateVisibility::Visible);
	
	return CachedPopup ? *CachedPopup : CreateWidget<UModioPopupBase>(this, PopupClass);;
}

UModioPopupBase* UModioPopupContainer::PopPopup(TSubclassOf<UModioPopupBase> PopupClass)
{
	if(PopupStack.Num())
	{
		PopupStack.Pop();
		if(PopupStack.Num())
		{
			return PopupStack.Last();
		}
	}

	// No more popups, hide ourselves
	SetVisibility(ESlateVisibility::Collapsed);
	
	return nullptr;
}