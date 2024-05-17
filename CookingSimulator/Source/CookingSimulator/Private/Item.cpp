// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "CookingSimulatorGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "ProceduralMeshComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh Comp"));
	baseMesh->SetupAttachment(RootComponent);
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

void AItem::DrawOutLine_Implementation(bool bOn)
{
	if (itemInfoStruct.itemType == ECookingSimulatorItemType::CookingTool)
	{
		if (baseMesh != nullptr)
		{
			baseMesh->SetRenderCustomDepth(bOn);

			baseMesh->SetCustomDepthStencilValue(bOn ? 1 : 0);
		}
	}
	else if (itemInfoStruct.itemType == ECookingSimulatorItemType::Ingredient)
	{
		if (proceduralMesh != nullptr)
		{
			proceduralMesh->SetRenderCustomDepth(bOn);
			
			proceduralMesh->SetCustomDepthStencilValue(bOn ? 1 : 0);
		}
	}
}

void AItem::InteractStart_Implementation()
{


}

void AItem::InteractEnd_Implementation()
{
}

