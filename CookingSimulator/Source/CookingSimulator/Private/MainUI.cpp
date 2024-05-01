// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableTextBox.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UMainUI::ShowNewOrder(bool bshow)
{
	if (bshow)
	{
		OrderTimeText->SetVisibility(ESlateVisibility::Visible);
		OrderText->SetVisibility(ESlateVisibility::Visible);
		OrderWindowImage->SetVisibility(ESlateVisibility::Visible);
		OrderFoodImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		OrderTimeText->SetVisibility(ESlateVisibility::Hidden);
		OrderText->SetVisibility(ESlateVisibility::Hidden);
		OrderWindowImage->SetVisibility(ESlateVisibility::Hidden);
		OrderFoodImage->SetVisibility(ESlateVisibility::Hidden);
	}
}