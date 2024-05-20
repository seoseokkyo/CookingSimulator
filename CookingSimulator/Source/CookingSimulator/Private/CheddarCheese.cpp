// Fill out your copyright notice in the Description page of Project Settings.


#include "CheddarCheese.h"

// Sets default values
ACheddarCheese::ACheddarCheese()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = TEXT("CheddarCheese");
}

// Called when the game starts or when spawned
void ACheddarCheese::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("CheddarCheese");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ACheddarCheese::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

