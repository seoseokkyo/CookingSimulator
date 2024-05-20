// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "CookingTool.generated.h"

/**
 * 
 */

 
UENUM(BlueprintType)
enum class ECookingToolType : uint8
{
	Knife,
	SaucePouch,
	Others
};

UCLASS()
class COOKINGSIMULATOR_API ACookingTool : public AItem
{
	GENERATED_BODY()
	
public:
	ECookingToolType toolType;
};
