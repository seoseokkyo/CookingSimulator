// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewOrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UNewOrderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UTextBlock* OrderTimeMinutes;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UTextBlock* OrderTimeSeconds;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UEditableTextBox* OrderText;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* OrderWindowImage;
	
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* timerBar;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* OrderFoodImage;

	UTexture2D* foodImage;

	float timer = 0;
	
	

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItemName(FString itemName);

	void HideWidget();

	// 새로운 주문이 들어왔을 때 위젯 활성화
	void NewOrder();

private:
	
	
	void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
