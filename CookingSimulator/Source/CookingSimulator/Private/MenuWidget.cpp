// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "MainUI.h"
#include "Components/CanvasPanel.h"
#include "Recipe_On_Monitor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NewOrderWidget.h"
#include "ResultWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/VerticalBox.h>
#include "Components/Overlay.h"

void UMenuWidget::NativeConstruct()
{
	UpdateCanTick();
	
	InitSubUI();
}

void UMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//NewOrder();
	
	//ShowResult();
}

void UMenuWidget::OpenGuide()
{
	mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Visible);
	mainUI->NewOrder();
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("xx")));
	recipeUI->RemoveFromParent();
	menuViewBox->AddChild(mainUI);
	//recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
	//newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::OpenRecipe()
{
	recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Visible);
	recipeUI->ShowRecipeOnMonitor();
	mainUI->RemoveFromParent();
	menuViewBox->AddChild(recipeUI);
	//mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
	//newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::NewOrder()
{
	if (true == bNewOrder)
	{
		bNewOrder = false;

		// 새로운 주문이 들어왔을 때 알려준다
		newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Visible);

		// 나머지 UI들을 숨긴다
		recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
		mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("o")));
	}
}

void UMenuWidget::ShowResult()
{
	if (true == bShowResult)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("bShowResult : TRUE")));

		resultUI->ShowResult();

		bShowResult = false;
		resultUI->ResultCanvas->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMenuWidget::InitSubUI()
{

	if (mainUI_BP != nullptr)
	{
		mainUI = CreateWidget<UMainUI>(GetWorld(), mainUI_BP);
		// 임시로 뷰포트에 띄움
		//mainUI->AddToViewport();
		menuViewBox->AddChild(mainUI);
		mainUI->SetRenderScale(FVector2D(1.0f));
		
		mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
		mainUI->HideWidget();
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("null")));
	}

	if (recipeUI_BP != nullptr)
	{
		recipeUI = CreateWidget<URecipe_On_Monitor>(GetWorld(), recipeUI_BP);
		// 임시로 뷰포트에 띄움
		//recipeUI->AddToViewport();
		menuViewBox->AddChild(recipeUI);
		recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);

		//recipeUI->SetRenderScale(FVector2D(2.0f, 1.0f));
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("o")));

	}

	if (newOrder_BP != nullptr)
	{
		newOrderUI = CreateWidget<UNewOrderWidget>(GetWorld(), newOrder_BP);
		// 임시로 뷰포트에 띄움
		newOrderUI->AddToViewport();
		newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
	}

	if (result_BP != nullptr)
	{
		resultUI = CreateWidget<UResultWidget>(GetWorld(), result_BP);
		resultUI->AddToViewport();
		resultUI->ResultCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
	GuideButton->OnReleased.AddDynamic(this, &UMenuWidget::OpenGuide);
	RecipeButton->OnReleased.AddDynamic(this, &UMenuWidget::OpenRecipe);
}

