// Fill out your copyright notice in the Description page of Project Settings.


#include "Tablet.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>
#include "MenuWidget.h"

ATablet::ATablet()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	// �º� �޽� ����
	tabletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tablet Meh Component"));
	tabletMeshComp->SetupAttachment(RootComponent);
	
	// ���� ������Ʈ ����
	menuWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget Componemnt"));
	menuWidgetComp->SetupAttachment(RootComponent);

}

void ATablet::BeginPlay()
{
	Super::BeginPlay();
	menuWidgetComp->SetWidgetClass(menuUI_BP);
}

void ATablet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

