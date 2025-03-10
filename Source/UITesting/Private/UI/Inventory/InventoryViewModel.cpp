// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryViewModel.h"

void UInventoryViewModel::SetTab(ECraftingCategory NewTab)
{
	if(SelectedTab != NewTab)
	{
		SelectedTab = NewTab;
		OnTabSelected.Broadcast(SelectedTab);
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
