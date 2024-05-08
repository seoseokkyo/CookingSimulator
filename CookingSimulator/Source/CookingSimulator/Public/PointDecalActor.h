// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "PointDecalActor.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API APointDecalActor : public ADecalActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	// 데칼 크기 설정
	FVector decalSizeSet = FVector(10, 10, 5);

	void SetShowDecal(bool visible);

protected:
	virtual void BeginPlay() override;
	
};
