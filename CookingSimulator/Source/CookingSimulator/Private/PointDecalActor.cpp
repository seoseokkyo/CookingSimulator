// Fill out your copyright notice in the Description page of Project Settings.


#include "PointDecalActor.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DecalActor.h>


void APointDecalActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetDecal()->DecalSize = decalRadius;
}

void APointDecalActor::SetShowDecal(bool visible)
{
	GetDecal()->SetVisibility(visible);
}