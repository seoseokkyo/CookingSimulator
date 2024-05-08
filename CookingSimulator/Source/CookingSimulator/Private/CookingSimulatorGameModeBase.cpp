// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameModeBase.h"
#include "CookingSimulatorGameInstance.h"

void ACookingSimulatorGameModeBase::StartPlay()
{
	Super::StartPlay();

	auto gameInstance = CastChecked<UCookingSimulatorGameInstance>(GetGameInstance());

	if (gameInstance != nullptr)
	{
		recipes.Reset();

		// 햄버거 레시피 작성
		{
			// 레시피 작성
			FCookingSimulatorRecipeInfo recipeDetail;

			recipeDetail.recipeName = TEXT("Hamburger");

			// 레시피 타입 설정
			recipeDetail.recipeType = ECookingSimulatorRecipeType::Hamburger;

			// 레시피 이미지 경로 설정 예시
			recipeDetail.recipeImagePath = "Content\\CookingSimulator\\Textures\\Hamburger.png";

			// 레시피 설명 설정 예시
			recipeDetail.recipeDescription = "This is Hamburger";

			// 레시피에 들어가는 식재료 설정
			recipeDetail.ingredientInfoArray.Reset();

			// 토마토 추가 예시
			FString ingredientName = TEXT("Tomato");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Onion");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Patty");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("BurgerBunUp");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("BurgerBunDown");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("CheddarCheese");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Ketchup");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Salt");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("BlackPepper");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			recipeDetail.cookingTimeLimit = 600;

			// 햄버거 레시피 작성 완료
			recipes.Add(recipeDetail);
		}

		// 연어스테이크와 삶은감자 레시피 작성
		{
			// 레시피 작성
			FCookingSimulatorRecipeInfo recipeDetail;

			recipeDetail.recipeName = TEXT("SalmonSteakAndBoiledPotato");

			// 레시피 타입 설정
			recipeDetail.recipeType = ECookingSimulatorRecipeType::SalmonSteakAndBoiledPotato;

			// 레시피 이미지 경로 설정 예시
			recipeDetail.recipeImagePath = "Content\\CookingSimulator\\Textures\\SalmonSteakAndBoiledPotato.png";

			// 레시피 설명 설정 예시
			recipeDetail.recipeDescription = "This is SalmonSteakAndBoiledPotato";

			// 레시피에 들어가는 식재료 설정
			recipeDetail.ingredientInfoArray.Reset();

			// 감자 추가 예시
			FString ingredientName = TEXT("Potato");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("SalmonSteak");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Water");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("SunflowerOil");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("Salt");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			ingredientName = TEXT("BlackPepper");
			recipeDetail.ingredientInfoArray.Add(FIngredientInfo(ingredientName, gameInstance->GetItemDataTable(ingredientName), 50, 100));

			recipeDetail.cookingTimeLimit = 600;

			// 연어스테이크와 삶은감자 레시피 작성 완료
			recipes.Add(recipeDetail);
		}
	}

	SetCurrentRecipe(ECookingSimulatorRecipeType::Hamburger);
}

void ACookingSimulatorGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
