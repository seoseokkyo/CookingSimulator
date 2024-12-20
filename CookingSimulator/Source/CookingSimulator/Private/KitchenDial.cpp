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

	toolType = ECookingToolType::Others;
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
			bStart = false;

			UE_LOG(LogTemp, Warning, TEXT("Timer End"));
		}
		else
		{
			if (bSecType)
			{
				dialMesh->SetRelativeRotation(FRotator(FMath::Lerp(0, 360, (currentTime + 360 - limitTime) / 360)*6, 0, 0));
			}
			else
			{
				dialMesh->SetRelativeRotation(FRotator(FMath::Lerp(0, 360, (currentTime + 3600 - limitTime) / 3600), 0, 0));
			}			
		}
	}
}

void AKitchenDial::SetTimer()
{	
	float rot = FRotator::ClampAxis(dialMesh->GetRelativeRotation().Clamp().Pitch);

	if (bSecType)
	{
		limitTime = (360 - rot) / 6;
	}
	else
	{
		limitTime = (360 - rot) * 10;
	}	

	limitTime = FMath::Clamp(limitTime, 0.f, 3599.f);

	bStart = true;

	FString strType(bSecType ? "Sec" : "Min");

	UE_LOG(LogTemp, Warning, TEXT("Timer Start ( Type : %s, Time : %f)"), *strType, limitTime);
}

void AKitchenDial::ResetTimer()
{
	bStart = false;
	limitTime = 0.0f;
	currentTime = 0.0f;

	dialMesh->SetRelativeRotation(FRotator::ZeroRotator);
}

