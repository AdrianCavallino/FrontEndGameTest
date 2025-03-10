// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"

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
