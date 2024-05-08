// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecipeOnMonitorListWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API URecipeOnMonitorListWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="MySetting", meta=(BindWidget))
	class UImage* ingrideintImage;

	UPROPERTY(EditAnywhere, Category="MySetting", meta=(BindWidget))
	class UTextBlock* ingrideintText;
};
