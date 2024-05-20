// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingredient.h"
#include "CookingSimulatorGameInstance.h"

//AIngredient::AIngredient(FString ingredientName)
//{
//	IngredientInfo = FIngredientInfo(ingredientName, itemInfoStruct, 100, 0);
//}

void AIngredient::HeatUP()
{
	IngredientInfo.ingredientCookedLevel += 1;
}

void AIngredient::InitIngredientInfo()
{
	auto gi = GetGameInstance<UCookingSimulatorGameInstance>();
	if (gi != nullptr)
	{
		IngredientInfo.ingredientInfo = gi->GetItemDataTable(IngredientInfo.ingredientName);
	}

	bUseProceduralMesh = true;
}
