// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UInventoryWidget;
class UInventoryViewModel;
/**
 * 
 */
UCLASS()
class AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Inventory")
	TSubclassOf<UInventoryViewModel> InventoryViewModelClass;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> InitialWidgetClass;

	UFUNCTION(BlueprintCallable)
	void ShowMenu();

private:
	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	UUserWidget* InitialWidget;
	
	UPROPERTY()
	UInventoryViewModel* InventoryViewModel;

	UPROPERTY()
	APlayerController* PlayerController;
};
