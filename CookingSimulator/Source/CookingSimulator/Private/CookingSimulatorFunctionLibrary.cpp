// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorFunctionLibrary.h"
#include <Kismet/KismetRenderingLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "CookingSimulatorGameInstance.h"
#include "Item.h"
#include <Misc/Paths.h>

UTexture2D* UCookingSimulatorFunctionLibrary::GetImageByItemName(UObject* WorldContextObject, const FString& rowName)
{
	UTexture2D* rtn = nullptr;

	auto gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

	if (gameInstance != nullptr)
	{

		auto cookingInstance = CastChecked<UCookingSimulatorGameInstance>(gameInstance);

		if (cookingInstance != nullptr)
		{

			FCookingSimulatorItemInfo itemInfo = cookingInstance->GetItemDataTable(rowName);

			rtn = UKismetRenderingLibrary::ImportFileAsTexture2D(WorldContextObject, FPaths::ProjectDir() + itemInfo.itemImagePath);
		}
	}

	return rtn;
}

UTexture2D* UCookingSimulatorFunctionLibrary::GetRecipeImage(UObject* WorldContextObject, ECookingSimulatorRecipeType recipeType)
{
	UTexture2D* rtn = nullptr;

	auto gameModeBase = UGameplayStatics::GetGameMode(WorldContextObject);

	if (gameModeBase != nullptr)
	{
		auto cookingModeBase = CastChecked<ACookingSimulatorGameModeBase>(gameModeBase);

		if (cookingModeBase != nullptr)
		{
			FCookingSimulatorRecipeInfo rcpInfo = cookingModeBase->GetRecipe((int)recipeType);

			rtn = UKismetRenderingLibrary::ImportFileAsTexture2D(WorldContextObject, FPaths::ProjectDir() + rcpInfo.recipeImagePath);
		}
	}

	return rtn;
}