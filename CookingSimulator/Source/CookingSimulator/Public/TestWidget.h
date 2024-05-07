// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidget.generated.h"

/**
 * 
 */

class UImage;
class AItem;
class UButton;
class UScrollBox;

UCLASS()
class COOKINGSIMULATOR_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	float ImageChangeDelay;

	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ¿¹½Ã¿ë
	TArray<FString> ItemNames;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UImage* ShowImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UButton* TimerStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UButton* TimerResetButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings", meta=(BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<UUserWidget> listWidget;

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItemName(FString itemName);

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItem(AItem* itemActor);

	UFUNCTION(BlueprintCallable)
	void OnClickedTimerStartButtom();
		
	UFUNCTION(BlueprintCallable)
	void OnClickedTimerResetButtom();

	UFUNCTION(BlueprintCallable)
	void InitList();
};
