// Fill out your copyright notice in the Description page of Project Settings.


#include "BigPot.h"
#include "Ingredient.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>

ABigPot::ABigPot()
{
	waterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterMesh"));
	waterMesh->SetupAttachment(baseMesh);
}

void ABigPot::BeginPlay()
{
}

void ABigPot::Tick(float DeltaTime)
{
	if (bBoilingStart)
	{
		currentTime += DeltaTime;

		if (currentTime > heatUpTimeOffset)
		{
			currentTime = 0.0f;

			Boiling();
		}
	}
}

void ABigPot::Boiling()
{
	for (auto Ingredient : InputIngredients)
	{
		Ingredient->HeatUP();

		const FIngredientInfo& info = Ingredient->GetIngredientInfo();

		FString strCurrentLevel = info.ingredientName;

		strCurrentLevel = strCurrentLevel + L" : " + FString::FromInt(info.ingredientCookedLevel);

		UKismetSystemLibrary::PrintString(GetWorld(), strCurrentLevel);
	}
}
