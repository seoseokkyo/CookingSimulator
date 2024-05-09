// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "LineDecalActor.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API ALineDecalActor : public ADecalActor
{
	GENERATED_BODY()

public:
	// ��Į ũ�� ����
	// FVector decalSizeSet = FVector(1, 1, 1);

	void SetShowDecal(bool visible);

protected:
	virtual void BeginPlay() override;
	
};
