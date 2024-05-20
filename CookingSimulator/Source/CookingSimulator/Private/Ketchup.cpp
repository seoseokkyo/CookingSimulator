// Fill out your copyright notice in the Description page of Project Settings.


#include "Ketchup.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineMeshComponent.h>

// Sets default values
AKetchup::AKetchup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//baseMesh->SetMobility(EComponentMobility::Static);

	splineComp = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineComponent"));
	splineComp->SetupAttachment(RootComponent);

	ItemName = TEXT("Ketchup");
}

// Called when the game starts or when spawned
void AKetchup::BeginPlay()
{
	Super::BeginPlay();

	IngredientInfo.ingredientName = TEXT("Ketchup");
	IngredientInfo.ingredientCookedLevel = 0;
	IngredientInfo.ingredientWeight = 0;

	InitIngredientInfo();
}

// Called every frame
void AKetchup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

