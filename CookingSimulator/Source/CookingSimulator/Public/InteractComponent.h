// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "InteractAbleInterface.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "InteractComponent.generated.h"

/**
 * 
 */
 DECLARE_DELEGATE(FInteractStart);

 DECLARE_DELEGATE(FInteractEnd);

UCLASS()
class COOKINGSIMULATOR_API UInteractComponent : public UStaticMeshComponent, public IInteractAbleInterface
{
	GENERATED_BODY()
	
public:
	virtual void DrawOutLine_Implementation(bool bOn) override;

	FInteractStart startEventDelegate;
	FInteractEnd endEventDelegate;

	bool bState = false;

	virtual void InteractStart_Implementation() override;

	virtual void InteractEnd_Implementation() override;
};
