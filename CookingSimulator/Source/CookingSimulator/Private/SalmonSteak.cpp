// Fill out your copyright notice in the Description page of Project Settings.


#include "SalmonSteak.h"

// Sets default values
ASalmonSteak::ASalmonSteak()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = TEXT("SalmonSteak");
}

// Called when the game starts or when spawned
void ASalmonSteak::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("SalmonSteak");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ASalmonSteak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

