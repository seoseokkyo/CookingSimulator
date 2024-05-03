// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include "CookingSimulatorGameInstance.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <Components/Image.h>
#include "Item.h"

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
}

void UTestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// BP에서도 비슷하게 해놓은 예시가 있음

	ImageChangeDelay += InDeltaTime;

	if (ImageChangeDelay > 3)
	{
		ImageChangeDelay = 0;
		ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetRecipeImage(GetWorld(), ECookingSimulatorRecipeType::Hamburger), true);
		//SetBrushImageByItemName(ItemNames[FMath::RandRange(0, 2)]);
	}	
}

void UTestWidget::SetBrushImageByItemName(FString itemName)
{
	ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName), true);
}

void UTestWidget::SetBrushImageByItem(AItem* itemActor)
{
	if (itemActor != nullptr)
	{
		ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemActor->ItemName), true);
	}
}