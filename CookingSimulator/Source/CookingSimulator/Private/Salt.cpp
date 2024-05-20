// Fill out your copyright notice in the Description page of Project Settings.


#include "Salt.h"

// Sets default values
ASalt::ASalt()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseProceduralMesh = false;

	ItemName = TEXT("Salt");
}

// Called when the game starts or when spawned
void ASalt::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("Salt");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ASalt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

