// Fill out your copyright notice in the Description page of Project Settings.


#include "KitchenKnife.h"

// Sets default values
AKitchenKnife::AKitchenKnife()
{
	knifeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KnifeMesh"));
	knifeMesh->SetupAttachment(RootComponent);

	ItemName = TEXT("FrenchKnife");
	toolType = ECookingToolType::Knife;
}

// Called when the game starts or when spawned
void AKitchenKnife::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKitchenKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

