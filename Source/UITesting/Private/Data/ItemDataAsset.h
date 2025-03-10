// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/Inventory/InventoryViewModel.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */

class UCraftingMaterial;
 
 
UCLASS(BlueprintType)
class UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TArray<FDataTableRowHandle> Items;

public:
	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> GetAllItems() const;
};
