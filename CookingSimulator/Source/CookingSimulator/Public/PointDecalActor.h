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
	// ��Į ũ�� ����
	FVector decalSizeSet = FVector(10, 10, 5);

	void SetShowDecal(bool visible);

protected:
	virtual void BeginPlay() override;
	
};
