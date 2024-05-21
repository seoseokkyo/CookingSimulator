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

	if (true == bNewOrder)
	{
		NewOrder();

		bNewOrder = false;
	}

	if (true == bShowResult)
	{
		ShowResult();
	}
}

void UMenuWidget::OpenGuide()
{
	mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Visible);
	mainUI->NewOrder();
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("xx")));
	
	// 다른 UI들을 지우고 Add Child 한다
	resultUI->RemoveFromParent();
	newOrderUI->RemoveFromParent();
	recipeUI->RemoveFromParent();
	
	menuViewBox->AddChild(mainUI);
	//recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
	//newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::OpenRecipe()
{

	
	// 다른 UI들을 지우고 Add Child 한다
	resultUI->RemoveFromParent();
	newOrderUI->RemoveFromParent();
	mainUI->RemoveFromParent();
	
	menuViewBox->AddChild(recipeUI);
	//mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
	//newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
	recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Visible);
	recipeUI->ShowRecipeOnMonitor();
}

void UMenuWidget::NewOrder()
{


	// 나머지 UI들을 숨긴다
	recipeUI->RemoveFromParent();
	mainUI->RemoveFromParent();

	resultUI->RemoveFromParent();
		
	// 새로운 주문이 들어왔을 때 알려준다
	menuViewBox->AddChild(newOrderUI);
	newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Visible);
	newOrderUI->NewOrder();
	
	//newOrderUI->SetVisibility(ESlateVisibility::Visible);

}

void UMenuWidget::ShowResult()
{
	
		//다른 UI들을 숨긴다
		recipeUI->RemoveFromParent();
		mainUI->RemoveFromParent();
		newOrderUI->RemoveFromParent();
		resultUI->RemoveFromParent();
		
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("bShowResult : TRUE")));

		resultUI->ShowResult();
		menuViewBox->AddChild(resultUI);

		bShowResult = false;
		resultUI->ResultCanvas->SetVisibility(ESlateVisibility::Visible);

		
	
}

void UMenuWidget::InitSubUI()
{
	if (newOrder_BP != nullptr)
	{
		newOrderUI = CreateWidget<UNewOrderWidget>(GetWorld(), newOrder_BP);


		// menuViewBox에 AddChild한다
		menuViewBox->AddChild(newOrderUI);
		newOrderUI->HideWidget();
		newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
	}

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


	if (result_BP != nullptr)
	{
		resultUI = CreateWidget<UResultWidget>(GetWorld(), result_BP);
		// menuViewBox에 AddChild한다
		menuViewBox->AddChild(resultUI);
		resultUI->ResultCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
	GuideButton->OnReleased.AddDynamic(this, &UMenuWidget::OpenGuide);
	RecipeButton->OnReleased.AddDynamic(this, &UMenuWidget::OpenRecipe);
}

void UMenuWidget::UpdateOrderUI(ESlateVisibility temp)
{
	if (temp == ESlateVisibility::Visible)
	{

	}	
}

