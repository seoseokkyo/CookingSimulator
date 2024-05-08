// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingredient.h"

//AIngredient::AIngredient(FString ingredientName)
//{
//	IngredientInfo = FIngredientInfo(ingredientName, itemInfoStruct, 100, 0);
//}

void AIngredient::HeatUP()
{
	IngredientInfo.ingredientCookedLevel += 1;
}
