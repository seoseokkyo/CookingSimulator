// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "CookingSimulatorGameInstance.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	auto gameInstance = GetGameInstance();

	if (gameInstance != nullptr)
	{
		auto cookingInstance = CastChecked<UCookingSimulatorGameInstance>(gameInstance);

		if (cookingInstance != nullptr)
		{
			if (!ItemName.IsEmpty())
			{
				itemInfoStruct = cookingInstance->GetItemDataTable(ItemName);
			}			
		}
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

