// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Recipe_On_Monitor.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API URecipe_On_Monitor : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* currentFood;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UScrollBox* recipeScrollBox;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UScrollBox* ingridientBox;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* recipeScroll;

	UTexture2D* foodImage;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class URecipeOnMonitorListWidget> ingridentList;
		
	UFUNCTION(BlueprintCallable)
	void ShowRecipeOnMonitor();
};
