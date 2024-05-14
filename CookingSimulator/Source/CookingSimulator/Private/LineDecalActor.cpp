// Fill out your copyright notice in the Description page of Project Settings.


#include "LineDecalActor.h"

#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DecalActor.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/DecalComponent.h>


void ALineDecalActor::BeginPlay()
{
	Super::BeginPlay();

	if (GetDecal() != nullptr)
	{
		GetDecal()->DecalSize = FVector(20);


	}
}

void ALineDecalActor::SetShowDecal(bool visible)
{
	if (GetDecal() != nullptr)
	{
		GetDecal()->SetVisibility(visible);
	}
}