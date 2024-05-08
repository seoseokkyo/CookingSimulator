// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Ingredient.generated.h"

/**
 * 
 */

 
USTRUCT(BlueprintType)
struct FIngredientInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FString ingredientName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FCookingSimulatorItemInfo ingredientInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int32 ingredientWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int32 ingredientCookedLevel;

	FIngredientInfo(){}

	FIngredientInfo(FString ingredientName, FCookingSimulatorItemInfo ingredientInfo, int32 ingredientWeight, int32 ingredientCookedLevel)
	{
		this->ingredientName = ingredientName;
		this->ingredientInfo = ingredientInfo;
		this->ingredientWeight = ingredientWeight;
		this->ingredientCookedLevel = ingredientCookedLevel;
	}
};


UCLASS()
class COOKINGSIMULATOR_API AIngredient : public AItem
{
	GENERATED_BODY()


private:
	FIngredientInfo IngredientInfo;
	
public:
	//AIngredient(FString ingredientName);

	void SetIngredientInfo(FIngredientInfo info) { IngredientInfo = info; };

	void HeatUP();

	FIngredientInfo GetIngredientInfo() { return IngredientInfo; };
	int32 GetCookedLevel() { return IngredientInfo.ingredientCookedLevel; };
};
