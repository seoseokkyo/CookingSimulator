// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UItemWidget::NativeConstruct()
{
	itemName->SetColorAndOpacity(FLinearColor::Black);
}
