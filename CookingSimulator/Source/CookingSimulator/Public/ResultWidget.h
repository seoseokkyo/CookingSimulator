// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// ���â 
	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UOverlay* Result;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UImage* CookedFood;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* TasteBar;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* SpendTimeBar;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* ScoreBar;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UTextBlock* ResultMenuName;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UCanvasPanel* ResultCanvas;
		
	UTexture2D* foodImage;

	// ��� â ���
	void ShowResult();

	void HideWidget();

private:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
