// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, Category = "MySettigns", meta = (BindWidget))
	class UImage* itemImage;

	UPROPERTY(EditAnywhere, Category = "MySettigns", meta = (BindWidget))
	class UTextBlock* itemName;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UCanvasPanel* itemCanvas;

private:

	virtual void NativeConstruct() override;
};
