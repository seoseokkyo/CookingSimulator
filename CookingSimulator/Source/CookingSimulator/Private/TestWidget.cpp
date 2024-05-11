// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include "CookingSimulatorGameInstance.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <Components/Image.h>
#include "Item.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "KitchenDial.h"
#include <../../../../../../../Source/Runtime/CoreUObject/Public/UObject/UObjectIterator.h>
#include "CookingSimulatorGameModeBase.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>
#include "ListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "BigPot.h"
#include "Potato.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ComboBoxString.h>
#include "Dumbwaiter.h"

void UTestWidget::NativeConstruct()
{
	//UpdateCanTick();

	ImageChangeDelay = 0;

	ItemNames.Reset();
	ItemNames.Add(TEXT("Tomato"));
	ItemNames.Add(TEXT("FrenchKnife"));
	ItemNames.Add(TEXT("Potato"));

	if (ShowImage != nullptr)
	{
		//SetBrushImageByItemName(ItemNames[0]);
		//ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), ECookingSimulatorRecipeType::Hamburger), true);
	}

	ShowImage->SetVisibility(ESlateVisibility::Hidden);
	
	TimerStartButton->OnClicked.AddDynamic(this, &UTestWidget::OnClickedTimerStartButtom);
	//TimerStartButton->SetVisibility(ESlateVisibility::Hidden);

	TimerResetButton->OnClicked.AddDynamic(this, &UTestWidget::OnClickedTimerResetButtom);
	//TimerResetButton->SetVisibility(ESlateVisibility::Hidden);

	ScrollBox->SetVisibility(ESlateVisibility::Hidden);
	
	RcpComboBox->AddOption(FString(TEXT("Hamburger")));
	RcpComboBox->AddOption(FString(TEXT("SalmonSteakAndBoiledPotato")));

	RcpComboBox->SetSelectedIndex(0);
}

void UTestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// BP에서도 비슷하게 해놓은 예시가 있음

	ImageChangeDelay += InDeltaTime;

	if (ImageChangeDelay > 3)
	{
		ImageChangeDelay = 0;
		ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), ECookingSimulatorRecipeType::Hamburger), false);
		//SetBrushImageByItemName(ItemNames[FMath::RandRange(0, 2)]);
	}	
}

void UTestWidget::SetBrushImageByItemName(FString itemName)
{
	ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName), false);
}

void UTestWidget::SetBrushImageByItem(AItem* itemActor)
{
	if (itemActor != nullptr)
	{
		ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemActor->ItemName), false);
	}
}

void UTestWidget::OnClickedTimerStartButtom()
{
	//for (TObjectIterator<AKitchenDial> It; It; ++It)
	//{
	//	if (AKitchenDial* dial = *It)
	//	{
	//		dial->SetTimer();
	//	}
	//}

	//for (TObjectIterator<ABigPot> It; It; ++It)
	//{
	//	if (ABigPot* dial = *It)
	//	{
	//		if (0)
	//		{
	//			dial->FillWater(true);
	//		}



	//		for (TObjectIterator<APotato> ItPotato; ItPotato; ++ItPotato)
	//		{
	//			if (APotato* potato = *ItPotato)
	//			{
	//				dial->AddIngredient(potato);
	//			}
	//		}
	//		
	//	}
	//}

	FCookingSimulatorRecipeInfo testRcp;
	
	// 버거
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Tomato"), FCookingSimulatorItemInfo(), 50, 40));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Onion"), FCookingSimulatorItemInfo(), 50, 40));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Patty"), FCookingSimulatorItemInfo(), 50, 60));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("BurgerBunUp"), FCookingSimulatorItemInfo(), 50, 40));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("BurgerBunDown"), FCookingSimulatorItemInfo(), 50, 50));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("CheddarCheese"), FCookingSimulatorItemInfo(), 50, 55));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Ketchup"), FCookingSimulatorItemInfo(), 50, 46));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Salt"), FCookingSimulatorItemInfo(), 50, 78));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("BlackPepper"), FCookingSimulatorItemInfo(), 50, 100));

	// 연어 스테이크
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Potato"), FCookingSimulatorItemInfo(), 50, 44));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("SalmonSteak"), FCookingSimulatorItemInfo(), 50, 45));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Water"), FCookingSimulatorItemInfo(), 50, 55));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("SunflowerOil"), FCookingSimulatorItemInfo(), 50, 56));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("Salt"), FCookingSimulatorItemInfo(), 50, 0));
	testRcp.ingredientInfoArray.Add(FIngredientInfo(TEXT("BlackPepper"), FCookingSimulatorItemInfo(), 50, 100));

	GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>()->CompareDeliveryFood(testRcp);
}

void UTestWidget::OnClickedTimerResetButtom()
{
	//for (TObjectIterator<AKitchenDial> It; It; ++It)
	//{
	//	if (AKitchenDial* dial = *It)
	//	{
	//		dial->ResetTimer();
	//	}
	//}

	//for (TObjectIterator<ABigPot> It; It; ++It)
	//{
	//	if (ABigPot* dial = *It)
	//	{
	//		dial->FillWater(false);
	//	}
	//}

	for (TObjectIterator<ADumbwaiter> It; It; ++It)
	{
		if (ADumbwaiter* dial = *It)
		{
			dial->FoodDelivery();
		}
	}
}

void UTestWidget::InitList()
{
	auto gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo currentRCP = gm->GetCurrentRecipe();

		int32 arraySize = currentRCP.ingredientInfoArray.Num()-1;

		for (int32 i = 0; i < arraySize; i++)
		{
			auto tempWidget = CreateWidget<UListWidget>(this, listWidget);

			ScrollBox->AddChild((UUserWidget*)tempWidget);

			tempWidget->ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), currentRCP.ingredientInfoArray[i].ingredientName), false);

			tempWidget->ShowText->SetText(FText::FromString(currentRCP.ingredientInfoArray[i].ingredientInfo.itemDescription));
		}
	}
}
