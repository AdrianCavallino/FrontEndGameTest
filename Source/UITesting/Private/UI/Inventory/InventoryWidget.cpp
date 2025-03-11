// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"

#include "GameplayTagContainer.h"
#include "Components/PanelWidget.h"
#include "Data/CraftingDataAsset.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::SetViewModel(UInventoryViewModel* NewViewModel)
{
	if (NewViewModel)
	{
		ViewModel = NewViewModel;
		InitializeChildWidget();

		OnViewModelSet.Broadcast();
	}
}

TArray<FInventoryItem> UInventoryWidget::FilterCraftingItem(UPanelWidget* InWidget, FGameplayTag Tag)
{
	if(!ViewModel) return {};

	TArray<UWidget*> AllWidget = InWidget->GetAllChildren();

	for (UWidget* Widget : AllWidget)
	{
		InWidget->RemoveChild(Widget);
	}

	if(Tag == FGameplayTag::EmptyTag) return ViewModel->GetAllCraftingItem();

	return ViewModel->GetFilteredCraftingItems(Tag);
}
