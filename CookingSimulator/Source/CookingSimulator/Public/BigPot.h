// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingTool.h"
#include "BigPot.generated.h"

/**
 * 
 */

 class UStaticMeshComponent;
 class AIngredient;

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

	TArray<AIngredient*> InputIngredients;

	void Boiling();

	bool bBoilingStart = false;

	// 10�ʿ� �ѹ��� ������ HeatUp�Լ� ȣ��
	float currentTime = 0.0f;
	float heatUpTimeOffset = 10.0f;

	virtual void InteractStart_Implementation() override;

public:
	ABigPot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings")
	UStaticMeshComponent* waterMesh;

	bool AddIngredient(AIngredient* Ingredient);

	void SetBoilState(bool bOn) { bBoilingStart = bOn; };

	void FillWater(bool bFill);
};
