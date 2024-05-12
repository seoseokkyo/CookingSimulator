// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UOverlay* MenuOverlay;

	UPROPERTY(EditAnywhere, Category="MySettings", meta = (BindWidget))
	class UButton* GuideButton;
	
	UPROPERTY(EditAnywhere, Category="MySettings", meta = (BindWidget))
	UButton* RecipeButton;

	UPROPERTY(EditAnywhere, Category ="MySettings")
	TSubclassOf<class URecipe_On_Monitor> recipeUI_BP;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class UMainUI> mainUI_BP;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class UNewOrderWidget> newOrder_BP;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class UResultWidget> result_BP;

	UPROPERTY(EditAnywhere, Category="MySettings")
	bool bNewOrder = false;

	UPROPERTY(EditAnywhere, Category="MySettings")
	bool bShowResult = false;

	class UMainUI* mainUI;

	class UResultWidget* resultUI;

	class URecipe_On_Monitor* recipeUI;

	class UNewOrderWidget* newOrderUI;


	UFUNCTION(BlueprintCallable)
	void OpenGuide();

	UFUNCTION(BlueprintCallable)
	void OpenRecipe();

	UFUNCTION(BlueprintCallable)
	void NewOrder();

	UFUNCTION(BlueprintCallable)
	void ShowResult();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};