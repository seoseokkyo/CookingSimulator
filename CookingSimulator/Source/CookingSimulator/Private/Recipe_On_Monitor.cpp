// Fill out your copyright notice in the Description page of Project Settings.


#include "Recipe_On_Monitor.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void URecipe_On_Monitor::ShowRecipeOnMonitor()
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();
		foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(),rcpInfo.recipeType);
		currentFood->SetBrushFromSoftTexture(foodImage);
		
		
		for (int32 i = 0; i < rcpInfo.ingredientInfoArray.Num() - 1; i++)
		{
			auto listTemp = CreateWidget(this, ingridentList,"RecipeOnMonitorListWidget");
			UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), rcpInfo.ingredientInfoArray[i].ingredientName);
			// 이미지 받아서 접근해야됨..
		}
	}

}
