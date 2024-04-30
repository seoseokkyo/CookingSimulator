// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameInstance.h"
#include "Item.h"

FCookingSimulatorItemInfo UCookingSimulatorGameInstance::GetItemDataTable(const FString& rowName)
{
	// 데이터 Parsing(분석) 하기
	FString errorText;
	FCookingSimulatorItemInfo* cookingSimulatorItemInfo = dt_itemDataTable->FindRow<FCookingSimulatorItemInfo>(FName(rowName), errorText);

	return *cookingSimulatorItemInfo;
}
