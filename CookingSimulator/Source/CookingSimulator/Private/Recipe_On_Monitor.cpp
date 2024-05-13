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
		// MonitorListWidget�� �ݺ��ؼ� CreateWidget�Ѵ�
		URecipeOnMonitorListWidget* listTemp = CreateWidget<URecipeOnMonitorListWidget>(this, ingridentList);
		
		// ���� �ֹ��� ���� �����ǿ��� ������ �̹����� �޾ƿ´�
		// �޾ƿ� �̹����� MonitorListWidget�� �̹��� �ڽ��� �Ҵ��Ѵ�
			if (listTemp != nullptr)
			{
				listTemp->ingrideintImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), rcpInfo.ingredientInfoArray[i].ingredientName), false);
		
				// ���� �ֹ��� ���� �����ǿ��� ������ �̸��� �޾ƿ´�
				// fstring ������ �̸��� ftext�� �ٲ۴�
				FText textTemp = FText::FromString(rcpInfo.ingredientInfoArray[i].ingredientName);
		
				// �޾ƿ� �̸����� MonitorListWidget�� �ؽ�Ʈ �ڽ��� �Ҵ��Ѵ�
				listTemp->ingrideintText->SetText(textTemp);
		
				// MonitorListWidget�� ��ũ�� �ڽ��� �Ҵ��Ѵ�.
				ingridientBox->AddChild(listTemp);			
				
				
			}
			
		}


		// ���� ������ Ÿ���� ������ ��
		if (rcpInfo.recipeType == ECookingSimulatorRecipeType::SalmonSteakAndBoiledPotato)
		{
			// ���� ���� �̹����� recipeScroll�� ����
			SalmonRecipeScrollBox->SetVisibility(ESlateVisibility::Visible);
			HamburgerRecipeScrollBox->SetVisibility(ESlateVisibility::Hidden);
			SalmonText->SetVisibility(ESlateVisibility::Visible);
			HamText->SetVisibility(ESlateVisibility::Hidden);
		}
		// ������ Ÿ���� ��� �ƴ϶��
		else
		{
			// �ܹ��� �̹����� recipeScroll�� ����
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

