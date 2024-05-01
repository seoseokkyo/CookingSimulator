// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include "CookingSimulatorGameInstance.h"
#include "CookingSimulatorFunctionLibrary.h"
#include <Components/Image.h>

void UTestWidget::SetBrushImageByItemName(FString itemName)
{
	ShowImage->SetBrushFromSoftTexture(UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName), true);
}
