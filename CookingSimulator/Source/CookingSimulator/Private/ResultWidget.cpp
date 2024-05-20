// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Overlay.h>
#include "CookingSimulatorFunctionLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include "Components/CanvasPanel.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"

void UResultWidget::NativeConstruct()
{
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();

		foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), rcpInfo.recipeType);
	}

}

void UResultWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	//ShowResult();
}

// �丮 ���â ���
void UResultWidget::ShowResult()
{
	if (CookedFood != nullptr)
	{
		ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
		if (gm != nullptr)
		{
			// �丮�� �������� ������ �ľ��ؼ� �׸��� �ؽ�Ʈ�� �ִ´�
			FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();
			FText textTemp = FText::FromString(rcpInfo.recipeName);
			ResultMenuName->SetText(textTemp);
			//ResultMenuName->SetRenderScale(FVector2D(0.5));
			CookedFood->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), rcpInfo.recipeType));

			// ������ ǥ���Ѵ�
			//ScoreBar->PercentDelegate.BindUFunction(this, FName(TEXT("GetScorePercent")));

			GetScorePercent();
		}
	}
}

void UResultWidget::SetResult(TArray<FString> comments, int32 rankPoint)
{
	resultComments = comments;


	getScore = rankPoint;
}

void UResultWidget::HideWidget()
{
	Result->SetVisibility(ESlateVisibility::Hidden);
}

float UResultWidget::GetScorePercent()
{
	float percent = getScore / 100.0f;

	ScoreBar->SetPercent(percent);

	return percent;
}

