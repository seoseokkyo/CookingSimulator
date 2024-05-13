// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackPepper.h"

// Sets default values
ABlackPepper::ABlackPepper()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlackPepper::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("BlackPepper");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void ABlackPepper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

