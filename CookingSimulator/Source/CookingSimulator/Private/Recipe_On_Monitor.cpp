// Fill out your copyright notice in the Description page of Project Settings.


#include "Recipe_On_Monitor.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>
#include "RecipeOnMonitorListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "Components/CanvasPanel.h"



void URecipe_On_Monitor::ShowRecipeOnMonitor()
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();
		foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(),rcpInfo.recipeType);
		currentFood->SetBrushFromSoftTexture(foodImage);
		
		ingridientBox->ClearChildren();

		for (int32 i = 0; i < rcpInfo.ingredientInfoArray.Num() - 1; i++)
		{
		// MonitorListWidget을 반복해서 CreateWidget한다
		URecipeOnMonitorListWidget* listTemp = CreateWidget<URecipeOnMonitorListWidget>(this, ingridentList);
		
		// 현재 주문이 들어온 레시피에서 재료들의 이미지를 받아온다
		// 받아온 이미지를 MonitorListWidget의 이미지 박스에 할당한다
			if (listTemp != nullptr)
			{
				listTemp->ingrideintImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), rcpInfo.ingredientInfoArray[i].ingredientName), false);
		
				// 현재 주문이 들어온 레시피에서 재료들의 이름을 받아온다
				// fstring 형식인 이름은 ftext로 바꾼다
				FText textTemp = FText::FromString(rcpInfo.ingredientInfoArray[i].ingredientName);
		
				// 받아온 이름들을 MonitorListWidget의 텍스트 박스에 할당한다
				listTemp->ingrideintText->SetText(textTemp);
		
				// MonitorListWidget을 스크롤 박스에 할당한다.
				ingridientBox->AddChild(listTemp);			
				
				
			}
			
		}


		// 현재 레시피 타입이 연어일 때
		if (rcpInfo.recipeType == ECookingSimulatorRecipeType::SalmonSteakAndBoiledPotato)
		{
			// 연어 구이 이미지를 recipeScroll에 띄운다
			SalmonRecipeScrollBox->SetVisibility(ESlateVisibility::Visible);
			HamburgerRecipeScrollBox->SetVisibility(ESlateVisibility::Hidden);
			SalmonText->SetVisibility(ESlateVisibility::Visible);
			HamText->SetVisibility(ESlateVisibility::Hidden);
		}
		// 레시피 타입이 연어가 아니라면
		else
		{
			// 햄버거 이미지를 recipeScroll에 띄운다
			SalmonRecipeScrollBox->SetVisibility(ESlateVisibility::Hidden);
			HamburgerRecipeScrollBox->SetVisibility(ESlateVisibility::Visible);
			HamText->SetVisibility(ESlateVisibility::Visible);
			SalmonText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	

}

void URecipe_On_Monitor::NativeConstruct()
{
	
}

