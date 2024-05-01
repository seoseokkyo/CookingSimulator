// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ingredient.h"
#include "CookingSimulatorGameModeBase.generated.h"

/**
 * 
 */

 
UENUM(BlueprintType)
enum class ECookingSimulatorRecipeType : uint8
{
	Hamburger,
	SalmonSteakAndBoiledPotato
};

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

USTRUCT(BlueprintType)
struct FCookingSimulatorRecipeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	ECookingSimulatorRecipeType recipeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	FString recipeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	FString recipeImagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	FString recipeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	TArray<FIngredientInfo> ingredientInfoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeInfo")
	float cookingTimeLimit;
};



UCLASS()
class COOKINGSIMULATOR_API ACookingSimulatorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	FCookingSimulatorRecipeInfo currentRecipe;
	bool bCooking;
	float cookingTimer;

protected:
	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recipe")
	TArray<FCookingSimulatorRecipeInfo> recipes;

	UFUNCTION(BlueprintCallable)
	bool SetCurrentRecipe(ECookingSimulatorRecipeType eType);

	UFUNCTION(BlueprintCallable)
	FCookingSimulatorRecipeInfo GetCurrentRecipe() { return currentRecipe;};

	UFUNCTION(BlueprintCallable)
	FCookingSimulatorRecipeInfo GetRecipe(int32 recipeIndex);

	UFUNCTION(BlueprintCallable)
	void CookingStart() { bCooking = true;};
};
