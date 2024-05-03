// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <CookingSimulatorGameModeBase.h>
#include "CookingSimulatorFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UCookingSimulatorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UTexture2D* GetImageByItemName(UObject* WorldContextObject, const FString& rowName);

	// ��� Beginplay�������� ��� ����
	UFUNCTION(BlueprintCallable)
	static UTexture2D* GetRecipeImage(UObject* WorldContextObject, ECookingSimulatorRecipeType recipeType);
};
