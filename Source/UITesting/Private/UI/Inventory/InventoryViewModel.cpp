// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryViewModel.h"

#include "Data/CraftingDataAsset.h"

void UInventoryViewModel::SetTab(FGameplayTag NewTabTag, UUserWidget* Widget)
{
	if(FilterTag != NewTabTag)
	{
		FilterTag = NewTabTag;
		OnTabSelected.Broadcast(FilterTag, Widget);
	}
}

void UInventoryViewModel::SetDisplayItem(const FInventoryItem& NewItem)
{
	if(SelectedItem != NewItem)
	{
		SelectedItem = NewItem;
		OnItemSelected.Broadcast(SelectedItem);
	}
}

TArray<FInventoryItem> UInventoryViewModel::GetAllCraftingItem() const
{
	if(!DummyCraftingData)
	{
		return {};
	}

	UCraftingDataAsset* DataAsset = Cast<UCraftingDataAsset>(DummyCraftingData);

	if(!DataAsset) return {};

	return DataAsset->GetAllItems();
}

TArray<FInventoryItem> UInventoryViewModel::GetFilteredCraftingItems(FGameplayTag Tag) const
{
	if(!DummyCraftingData)
	{
		return {};
	}

	const UCraftingDataAsset* DataAsset = Cast<UCraftingDataAsset>(DummyCraftingData);

	if(!DataAsset) return {};

	TArray<FInventoryItem> FilteredItem = {};

	return DataAsset->GetAllItems().FilterByPredicate([Tag](const FInventoryItem& Item)
	{
		return Item.ItemTag == Tag;
	});
}

TArray<FIngredients> UInventoryViewModel::GetCraftingIngridientsByRowName(FName RowName)
{
	if(!DummyCraftingData) return {};

	UCraftingDataAsset* DataAsset = Cast<UCraftingDataAsset>(DummyCraftingData);

	if(!DataAsset) return {};

	TArray<FCraftingItem> Items = DataAsset->CraftingItems;

	TArray<FIngredients> retVal;

	for (FCraftingItem Item : Items)
	{
		if(Item.CraftedItem.RowName == RowName)
		{
			for (FCraftingIngridients Ingridient : Item.Ingridients)
			{
				FInventoryTableRow* Row = Ingridient.Ingridient.DataTable->FindRow<FInventoryTableRow>(Ingridient.Ingridient.RowName, __FUNCTION__);

				if(!Row) continue;

				FIngredients Ing;
				Ing.ItemNeeded = Row->InventoryItem;
				Ing.AmountNeeded = Ingridient.Quantity;
				
				retVal.Add(Ing);
			}
		}
	}

	return retVal;
}
