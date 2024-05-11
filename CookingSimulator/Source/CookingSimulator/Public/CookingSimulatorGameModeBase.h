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
	int32 rankPoint = 100;

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
	ACookingSimulatorGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recipe")
	TArray<FCookingSimulatorRecipeInfo> recipes;

	UPROPERTY()
	int32 minutes = 5;

	UPROPERTY()
	int32 seconds;
		
	float cookingTimer = 300;

	UFUNCTION(BlueprintCallable)
	bool SetCurrentRecipe(ECookingSimulatorRecipeType eType);

	UFUNCTION(BlueprintCallable)
	FCookingSimulatorRecipeInfo GetCurrentRecipe() { return currentRecipe;};

	UFUNCTION(BlueprintCallable)
	FCookingSimulatorRecipeInfo GetRecipe(int32 recipeIndex);

	UFUNCTION(BlueprintCallable)
	void CookingStart() { bCooking = true;};

	UFUNCTION(BlueprintCallable)
	void CompareDeliveryFood(FCookingSimulatorRecipeInfo cookResult);
	
	UFUNCTION(BlueprintCallable)
	void CookingCountTime();
};
