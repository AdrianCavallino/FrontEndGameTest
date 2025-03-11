// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryViewModel.h"

#include "Data/CraftingDataAsset.h"
#include "Data/ItemDataAsset.h"

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

void UInventoryViewModel::PinCraftItem(const FInventoryItem& Item)
{
	if(PinnedCraftItems.Contains(Item))
	{
		PinnedCraftItems.Remove(Item);
	} else
	{
		PinnedCraftItems.Add(Item);
	}

	OnItemPinned.Broadcast(Item);
}

void UInventoryViewModel::PinInventoryItem(const FInventoryItem& Item)
{
	if(PinnedInventoryItem.Contains(Item))
	{
		PinnedInventoryItem.Remove(Item);
	} else
	{
		PinnedInventoryItem.Add(Item);
	}

	OnItemPinned.Broadcast(Item);
}

TArray<FInventoryItem> UInventoryViewModel::GetAllInventoryItem() const
{
	if(!DummyData) return {};

	UItemDataAsset* ItemDataAsset = Cast<UItemDataAsset>(DummyData);

	if(!ItemDataAsset) return {};

	if (PinnedInventoryItem.IsEmpty())
	{
		return ItemDataAsset->GetAllItems();
	}

	return ItemDataAsset->GetAllItems().FilterByPredicate([this](const FInventoryItem& Item)
	{
		return !PinnedInventoryItem.Contains(Item);
	});
}

TArray<FInventoryItem> UInventoryViewModel::GetAllCraftingItem() const
{
	if(!DummyCraftingData)
	{
		return {};
	}

	UCraftingDataAsset* DataAsset = Cast<UCraftingDataAsset>(DummyCraftingData);

	if(!DataAsset) return {};

	if(PinnedCraftItems.IsEmpty())
	{
		return DataAsset->GetAllItems();
	}

	return DataAsset->GetAllItems().FilterByPredicate([this](const FInventoryItem& Item)
	{
		return !PinnedCraftItems.Contains(Item);
	});
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

	if (PinnedCraftItems.IsEmpty())
	{
		return DataAsset->GetAllItems().FilterByPredicate([Tag, this](const FInventoryItem& Item)
	{
		return Item.ItemTag == Tag;
	});
	}

	return DataAsset->GetAllItems().FilterByPredicate([Tag, this](const FInventoryItem& Item)
	{
		return Item.ItemTag == Tag && !PinnedCraftItems.Contains(Item);
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
