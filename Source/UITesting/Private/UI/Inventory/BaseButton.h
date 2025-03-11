// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryViewModel.h"
#include "Blueprint/UserWidget.h"
#include "BaseButton.generated.h"


class UButton;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UBaseButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BaseButton;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnClick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHover();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void EnableButton();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DisableButton();
};
