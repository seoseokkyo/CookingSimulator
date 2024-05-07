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

void UTestWidget::NativeConstruct()
{
	UpdateCanTick();

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

	TimerResetButton->OnClicked.AddDynamic(this, &UTestWidget::OnClickedTimerResetButtom);
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
	for (TObjectIterator<AKitchenDial> It; It; ++It)
	{
		if (AKitchenDial* dial = *It)
		{
			dial->SetTimer();
		}
	}
}

void UTestWidget::OnClickedTimerResetButtom()
{
	for (TObjectIterator<AKitchenDial> It; It; ++It)
	{
		if (AKitchenDial* dial = *It)
		{
			dial->ResetTimer();
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
