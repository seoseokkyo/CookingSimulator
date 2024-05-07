// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListWidget.generated.h"

/**
 * 
 */

 class UImage;
 class UTextBlock;

UCLASS()
class COOKINGSIMULATOR_API UListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UImage* ShowImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UTextBlock* ShowText;


};
