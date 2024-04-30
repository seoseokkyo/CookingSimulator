// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CookingSimulatorGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COOKINGSIMULATOR_API UCookingSimulatorGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="MySettings")
	UDataTable* dt_itemDataTable;


	UFUNCTION(BlueprintCallable)
	FCookingSimulatorItemInfo GetItemDataTable(const FString& rowName);
};
