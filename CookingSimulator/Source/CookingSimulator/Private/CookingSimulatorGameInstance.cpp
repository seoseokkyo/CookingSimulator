// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingSimulatorGameInstance.h"
#include "Item.h"

FCookingSimulatorItemInfo UCookingSimulatorGameInstance::GetItemDataTable(const FString& rowName)
{
	FString errorText;
	FCookingSimulatorItemInfo* cookingSimulatorItemInfo = dt_itemDataTable->FindRow<FCookingSimulatorItemInfo>(FName(rowName), errorText);

	return *cookingSimulatorItemInfo;

	//if (rowName.Compare(TEXT("Empty")) == 0)
	//{
	//	return FCookingSimulatorItemInfo();
	//}
	//else
	//{
	//	return *cookingSimulatorItemInfo;
	//}	
}
