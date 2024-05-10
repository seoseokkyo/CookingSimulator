// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameModeBase.h"
#include "CookingSimulatorGameInstance.h"
#include "NewOrderWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>

void ACookingSimulatorGameModeBase::StartPlay()
{
	Super::StartPlay();

	//FTimerHandle timerHandle;
	//GetWorldTimerManager().SetTimer(timerHandle, this, &ACookingSimulatorGameModeBase::CookingCountTime, 5.f, false, 0.0f);

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

			recipeDetail.cookingTimeLimit = 300;

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

			recipeDetail.cookingTimeLimit = 300;

			// �������ũ�� �������� ������ �ۼ� �Ϸ�
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
		cookingTimer -= DeltaSeconds;

		if (cookingTimer <= 0)
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

			cookingTimer = currentRecipe.cookingTimeLimit;

			CookingCountTime();

			bCooking = true;

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

ACookingSimulatorGameModeBase::ACookingSimulatorGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACookingSimulatorGameModeBase::CookingCountTime()
{
	if (seconds != 0)
	{
		seconds -= 1;
	}
	else
	{
		if (minutes == 0)
		{

		}
		else
		{
			minutes -= 1;
			seconds = 59;
		}
	}
	
}
