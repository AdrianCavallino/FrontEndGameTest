// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataAsset.h"

TArray<FInventoryItem> UItemDataAsset::GetAllItems() const
{
	TArray<FInventoryItem> InventoryItems;
	
	for (FDataTableRowHandle Item : Items)
	{
		if(!Item.DataTable)
		{
			continue;
		}
		
		FInventoryTableRow* Row = Item.DataTable->FindRow<FInventoryTableRow>(Item.RowName, __FUNCTION__);
		if (Row)
		{
			InventoryItems.Add(Row->InventoryItem);
		}
	}

	return InventoryItems;
}
