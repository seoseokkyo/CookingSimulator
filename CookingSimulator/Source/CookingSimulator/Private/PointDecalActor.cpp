// Fill out your copyright notice in the Description page of Project Settings.


#include "PointDecalActor.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DecalActor.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/DecalComponent.h>


void APointDecalActor::BeginPlay()
{
	Super::BeginPlay();

	if (GetDecal() != nullptr)
	{
		GetDecal()->DecalSize = decalSizeSet;
	}
	UE_LOG(LogTemp,Warning,TEXT("decal"));
}

void APointDecalActor::SetShowDecal(bool visible)
{
	UE_LOG(LogTemp, Warning, TEXT("SetShowDecal Ptr : %p"), GetDecal());

	if (GetDecal() != nullptr)
	{
		GetDecal()->SetVisibility(visible);
	}	
}