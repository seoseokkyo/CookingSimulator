// Fill out your copyright notice in the Description page of Project Settings.


#include "KitchenDial.h"
#include <Components/StaticMeshComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine/StaticMesh.h>

// Sets default values
AKitchenDial::AKitchenDial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/KitchenTimer/Kitchen_timer_Body.Kitchen_timer_Body'")).Object);
	bodyMesh->SetupAttachment(RootComponent);

	dialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DialMesh"));
	dialMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/KitchenTimer/Kitchen_timer_Dial.Kitchen_timer_Dial'")).Object);
	dialMesh->SetupAttachment(bodyMesh);
	dialMesh->SetRelativeLocation(FVector(0, 1, 0));
}

// Called when the game starts or when spawned
void AKitchenDial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKitchenDial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		currentTime += DeltaTime;
		if (currentTime >= limitTime)
		{

		}
	}
}

void AKitchenDial::SetTimer()
{
	limitTime = dialMesh->GetRelativeRotation().Pitch * 10;
	//FMath::Clamp(limitTime, 0.f, 3599.f);

	bStart = true;
}

