// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "MainUI.h"
#include "Components/CanvasPanel.h"
#include "Recipe_On_Monitor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NewOrderWidget.h"
#include "ResultWidget.h"

void UMenuWidget::NativeConstruct()
{
	
	if (mainUI_BP != nullptr)
	{
		mainUI = CreateWidget<UMainUI>(GetWorld(), mainUI_BP);
		// �ӽ÷� ����Ʈ�� ���
		mainUI->AddToViewport();
		mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("null")));
	}
	
	if (recipeUI_BP != nullptr)
	{
		recipeUI = CreateWidget<URecipe_On_Monitor>(GetWorld(), recipeUI_BP);
		// �ӽ÷� ����Ʈ�� ���
		recipeUI->AddToViewport();
		recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("o")));
		
	}

	if (newOrder_BP != nullptr)
	{
		newOrderUI = CreateWidget<UNewOrderWidget>(GetWorld(), newOrder_BP);
		// �ӽ÷� ����Ʈ�� ���
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

void UMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	NewOrder();
	
	ShowResult();
}

void UMenuWidget::OpenGuide()
{
	mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Visible);
	recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
	newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::OpenRecipe()
{
	recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Visible);
	recipeUI->ShowRecipeOnMonitor();
	mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
	newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::NewOrder()
{
	if (true == bNewOrder)
	{
		bNewOrder = false;

		// ���ο� �ֹ��� ������ �� �˷��ش�
		newOrderUI->NewOrderCanvas->SetVisibility(ESlateVisibility::Visible);

		// ������ UI���� �����
		recipeUI->RecipeCanvas->SetVisibility(ESlateVisibility::Hidden);
		mainUI->GuideCanvas->SetVisibility(ESlateVisibility::Hidden);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("o")));
	}
}

void UMenuWidget::ShowResult()
{
	if (true == bShowResult)
	{
		bShowResult = false;
		resultUI->ResultCanvas->SetVisibility(ESlateVisibility::Visible);
	}
}

