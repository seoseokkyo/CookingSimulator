// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */

class UImage;
class AItem;

UCLASS()
class COOKINGSIMULATOR_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UTextBlock* OrderTimeText;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UEditableTextBox* OrderText;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* OrderWindowImage;
	
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* timerBar;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* OrderFoodImage;
	
	

	// 가이드 항목 1~22까지 있음
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide01;
	
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide02;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide03;
	
	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide04;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide05;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide06;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide07;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide08;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide09;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide10;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide11;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide12;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide13;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide14;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide15;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide16;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide17;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide18;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide19;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide20;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide21;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UImage* Guide22;

	UPROPERTY(EditAnywhere, Category="MySettings", meta=(BindWidget))
	class UOverlay* GuideBarOverlay;

	// 항목을 달성했을 때 교체할 이미지 1~22.
	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide01_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide02_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide03_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide04_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide05_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide06_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide07_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide08_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide09_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide10_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide11_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide12_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide13_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide14_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide15_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide16_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide17_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide18_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide19_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide20_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide21_Finish;

	UPROPERTY(EditAnywhere, Category="MySettings")
	UTexture2D* Guide22_Finish;


	// 결과창 
	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	UOverlay* Result;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	UImage* CookedFood;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* TasteBar;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* SpendTimeBar;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UProgressBar* ScoreBar;
		
	UTexture2D* foodImage;

	// 가이드 항목마다 bool 값이 있어서, 성공 여부에 따라 brush를 바꿔줌. 1~22까지 있음.
	bool bGuide01_Success = false;
	bool bGuide02_Success = false;
	bool bGuide03_Success = false;
	bool bGuide04_Success = false;
	bool bGuide05_Success = false;
	bool bGuide06_Success = false;
	bool bGuide07_Success = false;
	bool bGuide08_Success = false;
	bool bGuide09_Success = false;
	bool bGuide10_Success = false;
	bool bGuide11_Success = false;
	bool bGuide12_Success = false;
	bool bGuide13_Success = false;
	bool bGuide14_Success = false;
	bool bGuide15_Success = false;
	bool bGuide16_Success = false;
	bool bGuide17_Success = false;
	bool bGuide18_Success = false;
	bool bGuide19_Success = false;
	bool bGuide20_Success = false;
	bool bGuide21_Success = false;
	bool bGuide22_Success = false;

	// 새로운 주문이 들어왔을 때 알기 위한 bool 값.
	UPROPERTY(EditAnywhere, Category="MySettings")
	bool bNewOrder = false;

	// 새로운 주문이 들어왔을 때 위젯 활성화
	void NewOrder();

	// 연어 스테이크 레시피 가이드
	void SalmonGuide();

	// 결과 창 출력
	void ShowResult(FString itemName);

	UFUNCTION(BlueprintCallable)
	void SetBrushImageByItemName(FString itemName);
	
private:
	float ImageChangeDelay;
	
	TArray<FString> ItemNames;


	void NativeConstruct() override;
	

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// 위젯 숨기기
	void HideWidget();

	
	
};
