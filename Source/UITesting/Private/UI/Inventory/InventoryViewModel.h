// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Viewports.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "InventoryViewModel.generated.h"

UENUM(BlueprintType)
enum class ECraftingCategory : uint8
{
	ECT_All,
	ECT_Consumable,
	ECT_Building,
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	IC_Craft,
	IC_Material,
	IC_NormalItem,
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	bool operator!=(FInventoryItem Other) const
	{
		return ItemName != Other.ItemName;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag ItemTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 itemQuantity;
};

USTRUCT(BlueprintType)
struct FInventoryTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FInventoryItem InventoryItem;
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabSelected, ECraftingCategory, CraftingTab);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSelected,const FInventoryItem&, InventoryItem);


/**
 * 
 */
UCLASS(Blueprintable)
class UInventoryViewModel : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess = "true"))
	ECraftingCategory SelectedTab;
	
	UPROPERTY(BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess = "true"))
	FInventoryItem SelectedItem;
	
	UPROPERTY(BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess = "true"))
	TArray<FInventoryItem> CraftItems;

	UPROPERTY(BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess = "true"))
	TArray<FInventoryItem> PlayerInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dummy data", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset> DummyData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dummy data", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset> DummyCraftingData;


public:
	FOnTabSelected OnTabSelected;
	FOnItemSelected OnItemSelected;
	
	UFUNCTION(BlueprintCallable)
	void SetTab(ECraftingCategory NewTab);

	UFUNCTION(BlueprintCallable)
	void SetDisplayItem(const FInventoryItem& NewItem);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECraftingCategory GetSelectedTab() const { return SelectedTab; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FInventoryItem GetSelectedItem() const { return SelectedItem; }

	/*UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> GetFilteredCraftableItems();
    
	UFUNCTION(BlueprintCallable)
	bool CanCraftItem(const FInventoryItem& Item);*/
};
