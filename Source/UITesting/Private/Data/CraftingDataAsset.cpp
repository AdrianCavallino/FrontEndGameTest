// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CraftingDataAsset.h"

TArray<FCraftingIngridients> UCraftingDataAsset::GetIngridientsByItemId(FName ItemId)
{
	TArray<FCraftingIngridients> Ingridients;

	for (FCraftingItem Item : CraftingItems)
	{
		if(!Item.CraftedItem.DataTable)
		{
			continue;
		}

		if(Item.CraftedItem.RowName != ItemId) continue;
		
		Ingridients.Append(Item.Ingridients);
	}

	return Ingridients;
}

TArray<FInventoryItem> UCraftingDataAsset::GetAllItems() const
{
	TArray<FInventoryItem> InventoryItems;
	
	for (FCraftingItem Item : CraftingItems)
	{
		if(!Item.CraftedItem.DataTable)
		{
			continue;
		}
		
		FInventoryTableRow* Row = Item.CraftedItem.DataTable->FindRow<FInventoryTableRow>(Item.CraftedItem.RowName, __FUNCTION__);
		if (Row)
		{
			InventoryItems.Add(Row->InventoryItem);
		}
	}

	return InventoryItems;
}
