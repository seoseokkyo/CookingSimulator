// Fill out your copyright notice in the Description page of Project Settings.


#include "NewOrderWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableTextBox.h>
#include "CookingSimulatorGameModeBase.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>



void UNewOrderWidget::NativeConstruct()
{
	UpdateCanTick();
	
	//HideWidget();
	
	NewOrder();	
}

void UNewOrderWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();

	if (gm != nullptr)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("UNewOrderWidget::NativeTick %d : %d"), (int)(gm->cookingTimer) / 60, (int)(gm->cookingTimer) % 60));

		if (OrderTimeMinutes != nullptr)
		{
			OrderTimeMinutes->SetText(FText::FromString(FString::FromInt((int)(gm->cookingTimer) / 60)));
		}

		if (OrderTimeSeconds != nullptr)
		{
			OrderTimeSeconds->SetText(FText::FromString(FString::FromInt((int)(gm->cookingTimer) % 60)));
		}		
	}
}


void UNewOrderWidget::SetBrushImageByItemName(FString itemName)
{
	OrderFoodImage->SetBrushFromSoftTexture(foodImage);
	
}

void UNewOrderWidget::HideWidget()
{
	OrderTimeMinutes->SetVisibility(ESlateVisibility::Hidden);
	OrderTimeSeconds->SetVisibility(ESlateVisibility::Hidden);
	OrderText->SetVisibility(ESlateVisibility::Hidden);
	OrderWindowImage->SetVisibility(ESlateVisibility::Hidden);
	OrderFoodImage->SetVisibility(ESlateVisibility::Hidden);
	timerBar->SetVisibility(ESlateVisibility::Hidden);
}

// 새로운 주문이 들어왔을 때 위젯을 visible 상태로 바꾸고, 해당하는 이미지와 텍스트로 변경한다. 타이머 셋
void UNewOrderWidget::NewOrder()
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();

		OrderTimeMinutes->SetVisibility(ESlateVisibility::Visible);
		OrderTimeSeconds->SetVisibility(ESlateVisibility::Visible);
		OrderText->SetVisibility(ESlateVisibility::Visible);
		OrderWindowImage->SetVisibility(ESlateVisibility::Visible);
		OrderFoodImage->SetVisibility(ESlateVisibility::Visible);
		timerBar->SetVisibility(ESlateVisibility::Visible);

		foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), rcpInfo.recipeType);

		OrderFoodImage->SetBrushFromSoftTexture(foodImage);

		//FString minString = FString::FromInt(gm->minutes);
		//FText min = FText::FromString(minString);

		//FString secString = FString::FromInt(gm->seconds);
		//FText sec = FText::FromString(secString);
		


	}
}
