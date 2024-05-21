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
	
	// �ٸ� UI���� ����� Add Child �Ѵ�
	resultUI->RemoveFromParent();
	newOrderUI->RemoveFromParent();
	recipeUI->RemoveFromParent();
	
	menuViewBox->AddChild(mainUI);
	//recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
	//newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::OpenRecipe()
{

	
	// �ٸ� UI���� ����� Add Child �Ѵ�
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


	// ������ UI���� �����
	recipeUI->RemoveFromParent();
	mainUI->RemoveFromParent();

	resultUI->RemoveFromParent();
		
	// ���ο� �ֹ��� ������ �� �˷��ش�
	menuViewBox->AddChild(newOrderUI);
	newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Visible);
	newOrderUI->NewOrder();
	
	//newOrderUI->SetVisibility(ESlateVisibility::Visible);

}

void UMenuWidget::ShowResult()
{
	
		//�ٸ� UI���� �����
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


		// menuViewBox�� AddChild�Ѵ�
		menuViewBox->AddChild(newOrderUI);
		newOrderUI->HideWidget();
		newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
	}

	if (mainUI_BP != nullptr)
	{
		mainUI = CreateWidget<UMainUI>(GetWorld(), mainUI_BP);
		// �ӽ÷� ����Ʈ�� ���
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
		// �ӽ÷� ����Ʈ�� ���
		//recipeUI->AddToViewport();
		menuViewBox->AddChild(recipeUI);
		recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);

		//recipeUI->SetRenderScale(FVector2D(2.0f, 1.0f));
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("o")));

	}


	if (result_BP != nullptr)
	{
		resultUI = CreateWidget<UResultWidget>(GetWorld(), result_BP);
		// menuViewBox�� AddChild�Ѵ�
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

