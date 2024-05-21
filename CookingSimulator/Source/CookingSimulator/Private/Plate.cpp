// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "Ingredient.h"
#include <../../../../../../../Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h>

// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ECookingToolType::Others;

	ItemName = TEXT("Plate");
}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlate::plateActor(AActor* actor)
{
	actor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	auto ingredientCheck = Cast<AIngredient>(actor);

	if (ingredientCheck != nullptr)
	{
		if (platedActors.Num() > 0)
		{
			ingredientCheck->proceduralMesh->SetWorldLocation(platedActors[platedActors.Num() - 1]->GetActorLocation() + FVector(0, 0, 3), true);
		}
		else
		{
			ingredientCheck->proceduralMesh->SetWorldLocation(GetActorLocation() + FVector(0, 0, 3), true);
		}

		ingredientCheck->proceduralMesh->SetSimulatePhysics(false);
		ingredientCheck->proceduralMesh->SetRelativeRotation(FRotator(0));
	}
}

