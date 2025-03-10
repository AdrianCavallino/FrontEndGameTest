// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/Inventory/InventoryViewModel.h"
#include "CraftingDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCraftingIngridients
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle Ingridient;

	UPROPERTY(EditDefaultsOnly)
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FCraftingItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FCraftingIngridients> Ingridients;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle CraftedItem;
};

UCLASS(BlueprintType)
class UCraftingDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FCraftingItem> CraftingItems;

	UFUNCTION(BlueprintCallable)
	TArray<FCraftingIngridients> GetIngridientsByItemId( FName ItemId );

	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> GetAllItems() const;
	
};
