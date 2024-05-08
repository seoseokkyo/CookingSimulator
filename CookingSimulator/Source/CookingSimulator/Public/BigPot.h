// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingTool.h"
#include "BigPot.generated.h"

/**
 * 
 */

 class UStaticMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API ABigPot : public ACookingTool
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	TArray<class AIngredient*> InputIngredients;

	void Boiling();

	bool bBoilingStart = false;

	// 10초에 한번씩 재료들의 HeatUp함수 호출
	float currentTime = 0.0f;
	float heatUpTimeOffset = 10.0f;


public:
	ABigPot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings")
	UStaticMeshComponent* waterMesh;

	void SetBoilState(bool bOn) { bBoilingStart = bOn; };
};
