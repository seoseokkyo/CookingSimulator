// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidget.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class COOKINGSIMULATOR_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UImage* ShowImage;

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItemName(FString itemName);
};
