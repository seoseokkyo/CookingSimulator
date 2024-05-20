// Fill out your copyright notice in the Description page of Project Settings.


#include "Tomato.h"

// Sets default values
ATomato::ATomato()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = TEXT("Tomato");
}

// Called when the game starts or when spawned
void ATomato::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("Tomato");
	IngredientInfo.ingredientCookedLevel = 50;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ATomato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

