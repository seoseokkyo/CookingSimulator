// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingTool.h"
#include <Components/TimelineComponent.h>
#include "Dumbwaiter.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UInteractComponent;

UCLASS()
class COOKINGSIMULATOR_API ADumbwaiter : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADumbwaiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UStaticMeshComponent* leftDoor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UStaticMeshComponent* RightDoor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UStaticMeshComponent* buttonBody;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UInteractComponent* buttonTop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UInteractComponent* buttonBottom;
	
	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline leftDoorOpenTimeline;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline rightDoorOpenTimeline;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline upButtonPushTimeline;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FTimeline bottomButtonPushTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveLeftDoorOpen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveRightDoorOpen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveUpButtonPush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UCurveFloat* curveBottomButtonPush;

	bool bLeftDoorMove = false;
	bool bRightDoorMove = false;

	float leftDoorMoveTimer = 0.0f;
	float rightDoorMoveTimer = 0.0f;

	bool bUpButtonMove = false;
	bool bBottomButtonMove = false;

	float upButtonMoveTimer = 0.0f;
	float bottomButtonMoveTimer = 0.0f;

	UFUNCTION()
	void UpButtonTouch();

	UFUNCTION()
	void BottomButtonTouch();

	UFUNCTION()
	void LeftDoorMove(float Value);

	UFUNCTION()
	void RightDoorMove(float Value);

	UFUNCTION()
	void UpButtonMove(float Value);

	UFUNCTION()
	void BottomButtonMove(float Value);

	UFUNCTION()
	void UpButtonPushEndEvent();

	UFUNCTION()
	void BottomButtonPushEndEvent();

	UFUNCTION()
	void FoodDelivery();
};
