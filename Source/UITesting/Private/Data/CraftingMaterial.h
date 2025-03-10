// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CraftingMaterial.generated.h"

/**
 * 
 */
UCLASS()
class UCraftingMaterial : public UObject
{
	GENERATED_BODY()

private:
	FString MaterialName;

	double MaterialAmount;

public:

	/// Getter Setter for name
	FORCEINLINE FString GetMaterialName() const { return MaterialName; }
	FORCEINLINE void SetMaterialName(FString InMaterialName) { MaterialName = InMaterialName; }

	/// Getter Setter for amount
	FORCEINLINE double GetMaterialAmount() const { return MaterialAmount; }
	FORCEINLINE void SetMaterialAmount(double InMaterialAmount) { MaterialAmount = InMaterialAmount; }
};
