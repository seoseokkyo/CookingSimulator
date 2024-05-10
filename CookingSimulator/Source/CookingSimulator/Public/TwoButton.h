// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingTool.h"
#include <Components/TimelineComponent.h>
#include "InteractComponent.h"
#include "TwoButton.generated.h"

class UStaticMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API ATwoButton : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwoButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UInteractComponent* buttonTop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UInteractComponent* buttonBottom;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline upButtonPushTimeline;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline bottomButtonPushTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveUpButtonPush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveBottomButtonPush;

	//UFUNCTION()
	//void UpButtonTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void UpButtonTouch();

	//UFUNCTION()
	//void BottomButtonTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void BottomButtonTouch();

	UFUNCTION()
	void UpButtonMove(float Value);

	UFUNCTION()
	void BottomButtonMove(float Value);

	UFUNCTION()
	void UpButtonPushEndEvent();

	UFUNCTION()
	void BottomButtonPushEndEvent();
};
