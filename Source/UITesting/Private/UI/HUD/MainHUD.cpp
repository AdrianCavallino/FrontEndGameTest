// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MainHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Inventory/InventoryViewModel.h"
#include "UI/Inventory/InventoryWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!InventoryViewModel)
	{
		InventoryViewModel = NewObject<UInventoryViewModel>(this, InventoryViewModelClass);
	}
	//InitializeWidget();

	// Create and attach the Inventory Widget
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);

		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetViewModel(InventoryViewModel); // Pass ViewModel
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if(InitialWidgetClass)
	{
		InitialWidget = CreateWidget<UUserWidget>(GetWorld(), InitialWidgetClass);

		if(InitialWidget)
		{
			InitialWidget->AddToViewport();
		}
	}

	PlayerController = GetOwningPlayerController();
}

void AMainHUD::ShowMenu()
{
	if(!PlayerController) return;
	
	if(InventoryWidget->IsVisible())
	{
		InitialWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		InitialWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}
