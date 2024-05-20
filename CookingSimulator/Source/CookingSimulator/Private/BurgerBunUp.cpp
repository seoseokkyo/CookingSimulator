// Fill out your copyright notice in the Description page of Project Settings.


#include "BurgerBunUp.h"

// Sets default values
ABurgerBunUp::ABurgerBunUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = TEXT("BurgerBunUp");
}

// Called when the game starts or when spawned
void ABurgerBunUp::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("BurgerBunUp");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ABurgerBunUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

