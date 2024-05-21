// Fill out your copyright notice in the Description page of Project Settings.


#include "Mustard.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineMeshComponent.h>

// Sets default values
AMustard::AMustard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	splineComp = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineComponent"));
	splineComp->SetupAttachment(RootComponent);

	ItemName = TEXT("Mustard");
}

// Called when the game starts or when spawned
void AMustard::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("Mustard");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void AMustard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

