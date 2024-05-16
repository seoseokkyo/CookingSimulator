// Fill out your copyright notice in the Description page of Project Settings.


#include "BigPot.h"
#include "Ingredient.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>

void ABigPot::InteractStart_Implementation()
{
	Super::InteractStart_Implementation();

}

ABigPot::ABigPot()
{
	waterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterMesh"));
	waterMesh->SetupAttachment(baseMesh);
	waterMesh->SetRelativeScale3D(FVector(1, 1, 0));


	ItemName = TEXT("BigPot");
}

bool ABigPot::AddIngredient(AIngredient* Ingredient)
{
	FVector scaleTemp = waterMesh->GetRelativeScale3D();

	if (scaleTemp.Z > 0.7)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), L"Too Many Water");
		return false;
	}

	FVector placeLoc = GetActorLocation() + FVector(0, 0, scaleTemp.Z * 10);

	Ingredient->SetActorLocation(placeLoc);

	InputIngredients.Add(Ingredient);

	return true;
}

void ABigPot::FillWater(bool bFill)
{
	FVector scaleTemp = waterMesh->GetRelativeScale3D();
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scaleTemp X : %f, scaleTemp Y : %f, scaleTemp Z : %f"), scaleTemp.X, scaleTemp.Y, scaleTemp.Z));

	if (bFill)
	{
		scaleTemp.Z = FMath::Clamp(scaleTemp.Z + 0.1, 0, 1.08);

		if (scaleTemp.Z > 1)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), L"Pot FullFilledWater");
		}
	}
	else
	{
		scaleTemp.Z = FMath::Clamp(scaleTemp.Z - 0.1, 0, 1.08);

		if (scaleTemp.Z < 0.1)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), L"Pot Empty");
		}
	}

	waterMesh->SetRelativeScale3D(scaleTemp);
}

void ABigPot::BeginPlay()
{
	waterMesh->SetRelativeScale3D(FVector(1, 1, 0));
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
