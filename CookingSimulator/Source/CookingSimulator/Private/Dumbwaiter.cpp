// Fill out your copyright notice in the Description page of Project Settings.


#include "Dumbwaiter.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h>

// Sets default values
ADumbwaiter::ADumbwaiter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	baseMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Dumbwaiter/SM_DumbwaiterBody.SM_DumbwaiterBody'")).Object);

	// left door
	leftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	leftDoor->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Dumbwaiter/SM_DumbwaiterLeftDoor.SM_DumbwaiterLeftDoor'")).Object);
	leftDoor->SetupAttachment(baseMesh);
	leftDoor->SetRelativeLocation(FVector(-52.0f, 26.1f, -31.0f));

	// right door
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Dumbwaiter/SM_DumbwaiterRightDoor.SM_DumbwaiterRightDoor'")).Object);
	RightDoor->SetupAttachment(baseMesh);
	RightDoor->SetRelativeLocation(FVector(52.5f, 26.1f, -31.5f));	

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComp->SetupAttachment(baseMesh);
	boxComp->SetBoxExtent(FVector(50.0f, 26.0f, 32.0f));
}

// Called when the game starts or when spawned
void ADumbwaiter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADumbwaiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

