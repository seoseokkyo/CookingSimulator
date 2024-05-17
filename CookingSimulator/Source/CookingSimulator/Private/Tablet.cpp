// Fill out your copyright notice in the Description page of Project Settings.


#include "Tablet.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>

ATablet::ATablet()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	menuWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget Componemnt"));
	menuWidgetComp->SetupAttachment(RootComponent);

	tabletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tablet Meh Component"));
	tabletMeshComp->SetupAttachment(RootComponent);
}

void ATablet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATablet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

