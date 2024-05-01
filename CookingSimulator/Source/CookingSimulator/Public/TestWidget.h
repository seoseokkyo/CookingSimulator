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

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItemName(FString itemName);

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItem(AItem* itemActor);
};
