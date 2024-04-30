// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameModeBase.h"
#include "CookingSimulatorGameInstance.h"

void ACookingSimulatorGameModeBase::StartPlay()
{
	auto gameInstance = CastChecked<UCookingSimulatorGameInstance>(GetGameInstance());

	if (gameInstance != nullptr)
	{
		recipes.Reset();

		// �ܹ��� ������ �ۼ�
		{
			// ������ �ۼ�
			FCookingSimulatorRecipeInfo recipeDetail;

			recipeDetail.recipeName = TEXT("Hamburger");

			// ������ Ÿ�� ����
			recipeDetail.recipeType = ECookingSimulatorRecipeType::Hamburger;

			// ������ �̹��� ��� ���� ����
			recipeDetail.recipeImagePath = "Content\\CookingSimulator\\Textures\\Hamburger.png";

			// ������ ���� ���� ����
			recipeDetail.recipeDescription = "This is Hamburger";

			// �����ǿ� ���� ����� ����
			recipeDetail.ingredientInfoArray.Reset();

			// �丶�� �߰� ����
			FString ingredientName = TEXT("Tomato");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			recipeDetail.cookingTimeLimit = 600;

			// �ܹ��� ������ �ۼ� �Ϸ�
			recipes.Add(recipeDetail);
		}

		// �������ũ�� �������� ������ �ۼ�
		{
			// ������ �ۼ�
			FCookingSimulatorRecipeInfo recipeDetail;

			recipeDetail.recipeName = TEXT("SalmonSteakAndBoiledPotato");

			// ������ Ÿ�� ����
			recipeDetail.recipeType = ECookingSimulatorRecipeType::SalmonSteakAndBoiledPotato;

			// ������ �̹��� ��� ���� ����
			recipeDetail.recipeImagePath = "Content\\CookingSimulator\\Textures\\SalmonSteakAndBoiledPotato.png";

			// ������ ���� ���� ����
			recipeDetail.recipeDescription = "This is SalmonSteakAndBoiledPotato";

			// �����ǿ� ���� ����� ����
			recipeDetail.ingredientInfoArray.Reset();

			// ���� �߰� ����
			FString ingredientName = TEXT("Potato");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			recipeDetail.cookingTimeLimit = 600;

			// �������ũ�� �������� ������ �ۼ� �Ϸ�
			recipes.Add(recipeDetail);
		}
	}
}

void ACookingSimulatorGameModeBase::Tick(float DeltaSeconds)
{
	if (bCooking)
	{
		cookingTimer += DeltaSeconds;

		if (cookingTimer >= currentRecipe.cookingTimeLimit)
		{
			cookingTimer = 0;
			bCooking = false;

			UE_LOG(LogTemp, Warning, TEXT("Cook Time Over"));
		}
	}
}

bool ACookingSimulatorGameModeBase::SetCurrentRecipe(ECookingSimulatorRecipeType eType)
{
	//// Random
	//currentRecipe = recipes[FMath::RandRange(0, recipes.Num()-1)];

	for (const FCookingSimulatorRecipeInfo& rcpInfo : recipes)
	{
		if (rcpInfo.recipeType == eType)
		{
			currentRecipe = rcpInfo;

			return true;
		}
	}

	return false;
}

FCookingSimulatorRecipeInfo ACookingSimulatorGameModeBase::GetRecipe(int32 recipeIndex)
{
	if (recipes.Num() - 1 >= recipeIndex)
	{
		return recipes[recipeIndex];	
	}	

	return FCookingSimulatorRecipeInfo();
}