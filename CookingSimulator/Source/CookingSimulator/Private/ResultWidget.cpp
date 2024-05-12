// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Overlay.h>
#include "CookingSimulatorFunctionLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include "Components/CanvasPanel.h"

void UResultWidget::NativeConstruct()
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();

		foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), rcpInfo.recipeType);
	}

	ShowResult();
}

void UResultWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

// 요리 결과창 출력
void UResultWidget::ShowResult()
{
	if (CookedFood != nullptr)
	{
		ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
		if (gm != nullptr)
		{
			FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();
			FText textTemp = FText::FromString(rcpInfo.recipeName);
			ResultMenuName->SetText(textTemp);
			//ResultMenuName->SetRenderScale(FVector2D(0.5));
			CookedFood->SetBrushFromSoftTexture(foodImage);
		}
	}
}

void UResultWidget::HideWidget()
{
	Result->SetVisibility(ESlateVisibility::Hidden);
}

