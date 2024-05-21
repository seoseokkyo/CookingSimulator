// Fill out your copyright notice in the Description page of Project Settings.


#include "BurgerBunDown.h"

// Sets default values
ABurgerBunDown::ABurgerBunDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseProceduralMesh = true;

	ItemName = TEXT("BurgerBunDown");
}

// Called when the game starts or when spawned
void ABurgerBunDown::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("BurgerBunDown");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ABurgerBunDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

