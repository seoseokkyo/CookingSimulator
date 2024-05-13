// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameModeBase.h"
#include "CookingSimulatorGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "NewOrderWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>

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

			recipeDetail.cookingTimeLimit = 300;

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

			recipeDetail.cookingTimeLimit = 300;

			// 연어스테이크와 삶은감자 레시피 작성 완료
			recipes.Add(recipeDetail);
		}
	}

	//SetCurrentRecipe(ECookingSimulatorRecipeType::Hamburger);
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

void ACookingSimulatorGameModeBase::CompareDeliveryFood(FCookingSimulatorRecipeInfo cookResult)
{
	FCookingSimulatorRecipeInfo refRcp = GetCurrentRecipe();

	TArray<FIngredientInfo> refRcpList = refRcp.ingredientInfoArray;
	TArray<FIngredientInfo> cookResultList = cookResult.ingredientInfoArray;
	TArray<FString> resultComments;
	resultComments.Reset();

	TSet<int32> resultCheck;
	resultCheck.Reset();

	for (const auto ingredient : refRcpList)
	{
		bool bFind = false;
		int32 ingredientCookedLevel = 0;
		int32 ingredientWeight = 0;

		int32 count = 0;

		for (const auto resultIngredient : cookResultList)
		{
			if (resultIngredient.ingredientName.Len() > 0)
			{
				if (ingredient.ingredientName.Contains(resultIngredient.ingredientName))
				{
					bFind = true;

					ingredientCookedLevel = resultIngredient.ingredientCookedLevel;
					ingredientWeight = resultIngredient.ingredientWeight;

					resultCheck.Add(count);
				}
			}

			count++;
		}

		if (false == bFind)
		{
			resultComments.Add(FString::Printf(TEXT("%s가 없네요?"), *ingredient.ingredientName));

			cookResult.rankPoint -= 20;
		}
		else
		{
			if (ingredientCookedLevel < 45)
			{
				int32 commentIndex = FMath::RandRange(0, 1);

				switch (commentIndex)
				{
				case 0:
					resultComments.Add(FString::Printf(TEXT("%s가 덜 익었어요."), *ingredient.ingredientName));
					break;
				case 1:
					resultComments.Add(FString::Printf(TEXT("%s를 익히다 말았네요."), *ingredient.ingredientName));
					break;
				default:
					break;
				}

				cookResult.rankPoint -= 10;
			}
			else if (45 <= ingredientCookedLevel && ingredientCookedLevel <= 55)
			{
				resultComments.Add(FString::Printf(TEXT("%s가 완벽합니다."), *ingredient.ingredientName));
			}
			else
			{
				int32 commentIndex = FMath::RandRange(0, 1);

				switch (commentIndex)
				{
				case 0:
					resultComments.Add(FString::Printf(TEXT("%s가 새카맣게 탔네요."), *ingredient.ingredientName));
					break;
				case 1:
					resultComments.Add(FString::Printf(TEXT("%s를 연필 대신 써도 되겠어요."), *ingredient.ingredientName));
					break;
				default:
					break;
				}

				cookResult.rankPoint -= 10;
			}
		}
	}

	//TArray<bool> addedOtherIngredientCheck(false, cookResultList.Num());
	TArray<bool> addedOtherIngredientCheck;
	addedOtherIngredientCheck.Reset();
	addedOtherIngredientCheck.SetNum(cookResultList.Num());
	for (auto& temp : addedOtherIngredientCheck)
	{
		temp = false;
	}

	for (auto index : resultCheck)
	{
		addedOtherIngredientCheck[index] = true;
	}

	for (int32 i = 0; i <= cookResultList.Num() - 1; i++)
	{
		if (false == addedOtherIngredientCheck[i])
		{
			resultComments.Add(FString::Printf(TEXT("%s는 주문한 요리와 상관없는 재료입니다."), *cookResultList[i].ingredientName));
		}
	}

	for (auto resultComment : resultComments)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), resultComment, true, true, FLinearColor::Red, 10.0f);
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("요리 점수 : %03d"), cookResult.rankPoint), true, true, FLinearColor::Red, 10.0f);
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