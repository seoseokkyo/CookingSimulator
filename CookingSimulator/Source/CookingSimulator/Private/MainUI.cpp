// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/EditableTextBox.h>
#include <Components/Image.h>
#include "CookingSimulatorGameInstance.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <Components/Overlay.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/Texture2D.h>

void UMainUI::NativeConstruct()
{
	UpdateCanTick();

	ImageChangeDelay = 0;

	ItemNames.Reset();
	ItemNames.Add(TEXT("Tomato"));
	ItemNames.Add(TEXT("FrenchKnife"));
	ItemNames.Add(TEXT("Potato"));

	if (OrderFoodImage != nullptr)
	{
		SetBrushImageByItemName(ItemNames[0]);
	}

	HideWidget();

	// 임시 테스트
	ShowResult(ItemNames[0]);
}

void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// BP에서도 비슷하게 해놓은 예시가 있음

	ImageChangeDelay += InDeltaTime;

	if (ImageChangeDelay > 3)
	{
		ImageChangeDelay = 0;

		SetBrushImageByItemName(ItemNames[FMath::RandRange(0, 2)]);
	}

	NewOrder();
}

// 위젯 전체 숨기기
void UMainUI::HideWidget()
{
	OrderTimeText->SetVisibility(ESlateVisibility::Hidden);
	OrderText->SetVisibility(ESlateVisibility::Hidden);
	OrderWindowImage->SetVisibility(ESlateVisibility::Hidden);
	OrderFoodImage->SetVisibility(ESlateVisibility::Hidden);
	timerBar->SetVisibility(ESlateVisibility::Hidden);
	
	GuideBarOverlay->SetVisibility(ESlateVisibility::Hidden);
	
	Guide01->SetVisibility(ESlateVisibility::Hidden);
	Guide02->SetVisibility(ESlateVisibility::Hidden);
	Guide03->SetVisibility(ESlateVisibility::Hidden);
	Guide04->SetVisibility(ESlateVisibility::Hidden);
	Guide05->SetVisibility(ESlateVisibility::Hidden);
	Guide06->SetVisibility(ESlateVisibility::Hidden);
	Guide07->SetVisibility(ESlateVisibility::Hidden);
	Guide08->SetVisibility(ESlateVisibility::Hidden);
	Guide09->SetVisibility(ESlateVisibility::Hidden);
	Guide10->SetVisibility(ESlateVisibility::Hidden);
	Guide11->SetVisibility(ESlateVisibility::Hidden);
	Guide12->SetVisibility(ESlateVisibility::Hidden);
	Guide13->SetVisibility(ESlateVisibility::Hidden);
	Guide14->SetVisibility(ESlateVisibility::Hidden);
	Guide15->SetVisibility(ESlateVisibility::Hidden);
	Guide16->SetVisibility(ESlateVisibility::Hidden);
	Guide17->SetVisibility(ESlateVisibility::Hidden);
	Guide18->SetVisibility(ESlateVisibility::Hidden);
	Guide19->SetVisibility(ESlateVisibility::Hidden);
	Guide20->SetVisibility(ESlateVisibility::Hidden);
	Guide21->SetVisibility(ESlateVisibility::Hidden);
	Guide22->SetVisibility(ESlateVisibility::Hidden);

	//Result->SetVisibility(ESlateVisibility::Hidden);
}

// 새로운 주문이 들어왔을 때 bNewOrder == true가 된다. 그리고 새로운 주문 UI, 가이드 UI 띄운다.
void UMainUI::NewOrder()
{
	if (true == bNewOrder)
	{
		OrderTimeText->SetVisibility(ESlateVisibility::Visible);
		OrderText->SetVisibility(ESlateVisibility::Visible);
		OrderWindowImage->SetVisibility(ESlateVisibility::Visible);
		OrderFoodImage->SetVisibility(ESlateVisibility::Visible);
		timerBar->SetVisibility(ESlateVisibility::Visible);

		GuideBarOverlay->SetVisibility(ESlateVisibility::Visible);
			
	}
}

// 연어스테이크 레시피 가이드
void UMainUI::SalmonGuide()
{
	Guide01->SetVisibility(ESlateVisibility::Visible);

	if (true == bGuide01_Success)
	{
		Guide01->SetBrushFromTexture(Guide01_Finish, false);
		Guide02->SetVisibility(ESlateVisibility::Visible);
		Guide03->SetVisibility(ESlateVisibility::Visible);
		Guide04->SetVisibility(ESlateVisibility::Visible);
		Guide05->SetVisibility(ESlateVisibility::Visible);
		Guide06->SetVisibility(ESlateVisibility::Visible);
		Guide07->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide02_Success)
	{
		Guide02->SetBrushFromTexture(Guide02_Finish, false);
	}
	if (true == bGuide03_Success)
	{
		Guide03->SetBrushFromTexture(Guide03_Finish, false);
	}
	if (true == bGuide04_Success)
	{
		Guide04->SetBrushFromTexture(Guide04_Finish, false);
	}
	if (true == bGuide05_Success)
	{
		Guide05->SetBrushFromTexture(Guide05_Finish, false);
	}
	if (true == bGuide06_Success)
	{
		Guide06->SetBrushFromTexture(Guide06_Finish, false);
	}
	if (true == bGuide07_Success)
	{
		Guide07->SetBrushFromTexture(Guide07_Finish, false);
		Guide08->SetVisibility(ESlateVisibility::Visible);
		Guide09->SetVisibility(ESlateVisibility::Visible);
		Guide10->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide08_Success)
	{
		Guide08->SetBrushFromTexture(Guide08_Finish, false);
	}
	if (true == bGuide09_Success)
	{
		Guide09->SetBrushFromTexture(Guide09_Finish, false);
	}
	if (true == bGuide10_Success)
	{
		Guide10->SetBrushFromTexture(Guide10_Finish, false);
		Guide11->SetVisibility(ESlateVisibility::Visible);
		Guide12->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide11_Success)
	{
		Guide11->SetBrushFromTexture(Guide11_Finish, false);
	}
	if (true == bGuide12_Success)
	{
		Guide12->SetBrushFromTexture(Guide12_Finish, false);
		Guide13->SetVisibility(ESlateVisibility::Visible);
		Guide14->SetVisibility(ESlateVisibility::Visible);
		Guide15->SetVisibility(ESlateVisibility::Visible);
		Guide16->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide13_Success)
	{
		Guide13->SetBrushFromTexture(Guide13_Finish, false);
	}
	if (true == bGuide14_Success)
	{
		Guide14->SetBrushFromTexture(Guide14_Finish, false);
	}
	if (true == bGuide15_Success)
	{
		Guide15->SetBrushFromTexture(Guide15_Finish, false);
	}
	if (true == bGuide16_Success)
	{
		Guide16->SetBrushFromTexture(Guide16_Finish, false);
		Guide17->SetVisibility(ESlateVisibility::Visible);
		Guide18->SetVisibility(ESlateVisibility::Visible);
		Guide19->SetVisibility(ESlateVisibility::Visible);
		Guide20->SetVisibility(ESlateVisibility::Visible);
		Guide21->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide17_Success)
	{
		Guide17->SetBrushFromTexture(Guide17_Finish, false);
	}
	if (true == bGuide18_Success)
	{
		Guide18->SetBrushFromTexture(Guide18_Finish, false);
	}
	if (true == bGuide19_Success)
	{
		Guide19->SetBrushFromTexture(Guide19_Finish, false);
	}
	if (true == bGuide20_Success)
	{
		Guide20->SetBrushFromTexture(Guide20_Finish, false);
	}
	if (true == bGuide21_Success)
	{
		Guide21->SetBrushFromTexture(Guide21_Finish, false);
		Guide22->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide22_Success)
	{
		HideWidget();
	}
}

void UMainUI::ShowResult(FString itemName)
{
	if (CookedFood != nullptr)
	{
		CookedFood->SetBrushFromSoftTexture(foodImage, false);
	}
}

void UMainUI::SetBrushImageByItemName(FString itemName)
{
	foodImage = UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName);
	OrderFoodImage->SetBrushFromSoftTexture(foodImage, false);
}

