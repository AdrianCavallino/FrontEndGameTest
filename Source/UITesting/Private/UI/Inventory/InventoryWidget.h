// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventoryViewModel.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnViewModelSet);

class UInventoryViewModel;
/**
 * 
 */
UCLASS()
class UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="ViewModel")
	TObjectPtr<UInventoryViewModel> ViewModel;
	
	virtual void NativeConstruct() override;

private:
	/* TODO: Add the Widget Component here */

	/* END : Component */

public:
	UPROPERTY(BlueprintAssignable)
	FOnViewModelSet OnViewModelSet;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInventoryViewModel* GetViewModel() const { return ViewModel; }
	
	UFUNCTION(BlueprintCallable)
	virtual void SetViewModel(UInventoryViewModel* NewViewModel);

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeChildWidget();

	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> FilterCraftingItem(UPanelWidget* InWidget, FGameplayTag Tag);
};
