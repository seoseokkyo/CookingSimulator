// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/EditableTextBox.h>
#include <Components/Image.h>
#include "CookingSimulatorGameInstance.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <Components/Overlay.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/Texture2D.h>
#include "CookingSimulatorGameModeBase.h"

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

}

void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

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

	HamGuide01->SetVisibility(ESlateVisibility::Hidden);
	HamGuide02->SetVisibility(ESlateVisibility::Hidden);
	HamGuide03->SetVisibility(ESlateVisibility::Hidden);
	HamGuide04->SetVisibility(ESlateVisibility::Hidden);
	HamGuide05->SetVisibility(ESlateVisibility::Hidden);
	HamGuide06->SetVisibility(ESlateVisibility::Hidden);
	HamGuide07->SetVisibility(ESlateVisibility::Hidden);
	HamGuide08->SetVisibility(ESlateVisibility::Hidden);
	HamGuide09->SetVisibility(ESlateVisibility::Hidden);
	HamGuide10->SetVisibility(ESlateVisibility::Hidden);
	HamGuide11->SetVisibility(ESlateVisibility::Hidden);
	HamGuide12->SetVisibility(ESlateVisibility::Hidden);
	HamGuide13->SetVisibility(ESlateVisibility::Hidden);
	HamGuide14->SetVisibility(ESlateVisibility::Hidden);

	Result->SetVisibility(ESlateVisibility::Hidden);
}

// 새로운 주문이 들어왔을 때 bNewOrder == true가 된다. 그리고 새로운 주문 UI, 가이드 UI 띄운다.
void UMainUI::NewOrder()
{
	//if (true == bNewOrder)
	//{
		bNewOrder = false;

		ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
		if (gm != nullptr)
		{
			FCookingSimulatorRecipeInfo rcpInfo = gm->GetCurrentRecipe();

			OrderTimeText->SetVisibility(ESlateVisibility::Visible);
			OrderText->SetVisibility(ESlateVisibility::Visible);
			OrderWindowImage->SetVisibility(ESlateVisibility::Visible);
			OrderFoodImage->SetVisibility(ESlateVisibility::Visible);
			timerBar->SetVisibility(ESlateVisibility::Visible);

			GuideBarOverlay->SetVisibility(ESlateVisibility::Visible);

			FText textTemp = FText::FromString(rcpInfo.recipeName);

			UE_LOG(LogTemp, Warning, TEXT("Rcp Name : %s"), *rcpInfo.recipeName);

			Menu->SetText(textTemp);
			Menu->SetColorAndOpacity(FLinearColor::Black);

			foodImage = UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), rcpInfo.recipeType);

			OrderFoodImage->SetBrushFromSoftTexture(foodImage);

			// 임시 테스트
			ShowResult(rcpInfo.recipeName);

			if (rcpInfo.recipeType == ECookingSimulatorRecipeType::Hamburger)
			{
				HamburgerGuide();
			}
			else if (rcpInfo.recipeType == ECookingSimulatorRecipeType::SalmonSteakAndBoiledPotato)
			{
				SalmonGuide();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Recipe Type Error"));
			}
		}			
	//}
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
		SetOriginImage();
	}
}

// 햄버거 레시피 가이드
void UMainUI::HamburgerGuide()
{
	HamGuide01->SetVisibility(ESlateVisibility::Visible);
	HamGuide02->SetVisibility(ESlateVisibility::Visible);
	HamGuide03->SetVisibility(ESlateVisibility::Visible);

	if (true == bGuide01_Success)
	{
		HamGuide01->SetBrushFromTexture(HamGuide01_Finish);
	}
	if (true == bGuide02_Success)
	{
		HamGuide02->SetBrushFromTexture(HamGuide02_Finish);
	}
	if (true == bGuide03_Success)
	{
		HamGuide03->SetBrushFromTexture(HamGuide03_Finish);
		HamGuide04->SetVisibility(ESlateVisibility::Visible);
		HamGuide05->SetVisibility(ESlateVisibility::Visible);
		HamGuide06->SetVisibility(ESlateVisibility::Visible);
		HamGuide07->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide04_Success)
	{
		HamGuide04->SetBrushFromTexture(HamGuide04_Finish);
	}
	if (true == bGuide05_Success)
	{
		HamGuide05->SetBrushFromTexture(HamGuide05_Finish);
	}
	if (true == bGuide06_Success)
	{
		HamGuide06->SetBrushFromTexture(HamGuide06_Finish);
	}
	if (true == bGuide07_Success)
	{
		HamGuide07->SetBrushFromTexture(HamGuide07_Finish);
		HamGuide08->SetVisibility(ESlateVisibility::Visible);
		HamGuide09->SetVisibility(ESlateVisibility::Visible);
		HamGuide10->SetVisibility(ESlateVisibility::Visible);
		HamGuide11->SetVisibility(ESlateVisibility::Visible);
		HamGuide12->SetVisibility(ESlateVisibility::Visible);
		HamGuide13->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide08_Success)
	{
		HamGuide08->SetBrushFromTexture(HamGuide08_Finish);
	}
	if (true == bGuide09_Success)
	{
		HamGuide09->SetBrushFromTexture(HamGuide09_Finish);
	}
	if (true == bGuide10_Success)
	{
		HamGuide10->SetBrushFromTexture(HamGuide10_Finish);
	}
	if (true == bGuide11_Success)
	{
		HamGuide11->SetBrushFromTexture(HamGuide11_Finish);
	}
	if (true == bGuide12_Success)
	{
		HamGuide12->SetBrushFromTexture(HamGuide12_Finish);
	}
	if (true == bGuide13_Success)
	{
		HamGuide13->SetBrushFromTexture(HamGuide13_Finish);
		HamGuide14->SetVisibility(ESlateVisibility::Visible);
	}
	if (true == bGuide14_Success)
	{
		HideWidget();
		SetOriginImage();
	}
}

// 요리 결과창 출력
void UMainUI::ShowResult(FString itemName)
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

// 요리 완성 후에 레시피 가이드 원래대로 돌리기
void UMainUI::SetOriginImage()
{
	// 연어 레시피 미완 상태로 돌리기
	Guide01->SetBrushFromTexture(Guide01_Image);
	Guide02->SetBrushFromTexture(Guide02_Image);
	Guide03->SetBrushFromTexture(Guide03_Image);
	Guide04->SetBrushFromTexture(Guide04_Image);
	Guide05->SetBrushFromTexture(Guide05_Image);
	Guide06->SetBrushFromTexture(Guide06_Image);
	Guide07->SetBrushFromTexture(Guide07_Image);
	Guide08->SetBrushFromTexture(Guide08_Image);
	Guide09->SetBrushFromTexture(Guide09_Image);
	Guide10->SetBrushFromTexture(Guide10_Image);
	Guide11->SetBrushFromTexture(Guide11_Image);
	Guide12->SetBrushFromTexture(Guide12_Image);
	Guide13->SetBrushFromTexture(Guide13_Image);
	Guide14->SetBrushFromTexture(Guide14_Image);
	Guide15->SetBrushFromTexture(Guide15_Image);
	Guide16->SetBrushFromTexture(Guide16_Image);
	Guide17->SetBrushFromTexture(Guide17_Image);
	Guide18->SetBrushFromTexture(Guide18_Image);
	Guide19->SetBrushFromTexture(Guide19_Image);
	Guide20->SetBrushFromTexture(Guide20_Image);
	Guide21->SetBrushFromTexture(Guide21_Image);
	Guide22->SetBrushFromTexture(Guide22_Image);


	// 햄버거 미완상태로 돌리기
	HamGuide01->SetBrushFromTexture(HamGuide01_Image);
	HamGuide02->SetBrushFromTexture(HamGuide02_Image);
	HamGuide03->SetBrushFromTexture(HamGuide03_Image);
	HamGuide04->SetBrushFromTexture(HamGuide04_Image);
	HamGuide05->SetBrushFromTexture(HamGuide05_Image);
	HamGuide06->SetBrushFromTexture(HamGuide06_Image);
	HamGuide07->SetBrushFromTexture(HamGuide07_Image);
	HamGuide08->SetBrushFromTexture(HamGuide08_Image);
	HamGuide09->SetBrushFromTexture(HamGuide09_Image);
	HamGuide10->SetBrushFromTexture(HamGuide10_Image);
	HamGuide11->SetBrushFromTexture(HamGuide11_Image);
	HamGuide12->SetBrushFromTexture(HamGuide12_Image);
	HamGuide13->SetBrushFromTexture(HamGuide13_Image);
	HamGuide14->SetBrushFromTexture(HamGuide14_Image);

	bGuide01_Success = false;
	bGuide02_Success = false;
	bGuide03_Success = false;
	bGuide04_Success = false;
	bGuide05_Success = false;
	bGuide06_Success = false;
	bGuide07_Success = false;
	bGuide08_Success = false;
	bGuide09_Success = false;
	bGuide10_Success = false;
	bGuide11_Success = false;
	bGuide12_Success = false;
	bGuide13_Success = false;
	bGuide14_Success = false;
	bGuide15_Success = false;
	bGuide16_Success = false;
	bGuide17_Success = false;
	bGuide18_Success = false;
	bGuide19_Success = false;
	bGuide20_Success = false;
	bGuide21_Success = false;
	bGuide22_Success = false;
}

void UMainUI::SetBrushImageByItemName(FString itemName)
{
	//foodImage = UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName);
	OrderFoodImage->SetBrushFromSoftTexture(foodImage);
}

