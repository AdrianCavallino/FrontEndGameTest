// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/BaseButton.h"

#include "Components/Button.h"

void UBaseButton::NativeConstruct()
{
	Super::NativeConstruct();

	BaseButton->OnClicked.AddDynamic(this, &UBaseButton::OnClick);
	BaseButton->OnHovered.AddDynamic(this, &UBaseButton::OnHover);
}

void UBaseButton::NativeDestruct()
{
	BaseButton->OnClicked.RemoveDynamic(this, &UBaseButton::OnClick);
	BaseButton->OnHovered.RemoveDynamic(this, &UBaseButton::OnHover);
	
	Super::NativeDestruct();
}

