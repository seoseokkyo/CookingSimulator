// Fill out your copyright notice in the Descriptiof page of Project Settings.


#include "Dumbwaiter.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <Kismet/KismetSystemLibrary.h>
#include "InteractComponent.h"
#include "CookingSimulatorGameModeBase.h"

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

	buttonBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Body"));
	buttonBody->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonBody.ButtonBody'")).Object);
	buttonBody->SetupAttachment(baseMesh);
	buttonBody->SetRelativeLocation(FVector(55.5f, 27.1f, -27.0f));
	buttonBody->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	buttonTop = CreateDefaultSubobject<UInteractComponent>(TEXT("Button Top"));
	buttonTop->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonTop.ButtonTop'")).Object);
	buttonTop->SetupAttachment(baseMesh);
	buttonTop->SetRelativeLocation(FVector(55.5f, 28.1f, -24.3f));
	buttonTop->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	buttonBottom = CreateDefaultSubobject<UInteractComponent>(TEXT("Button Bottom"));
	buttonBottom->SetupAttachment(baseMesh);
	buttonBottom->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonBottom.ButtonBottom'")).Object);
	buttonBottom->SetRelativeLocation(FVector((55.5f, 28.1f, -29.6f)));
	buttonBottom->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
}

// Called when the game starts or when spawned
void ADumbwaiter::BeginPlay()
{
	Super::BeginPlay();

	if (curveLeftDoorOpen)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADumbwaiter::LeftDoorMove);
		leftDoorOpenTimeline.AddInterpFloat(curveLeftDoorOpen, TimelineProgress);
	}

	if (curveRightDoorOpen)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADumbwaiter::RightDoorMove);
		rightDoorOpenTimeline.AddInterpFloat(curveRightDoorOpen, TimelineProgress);
	}

	if (curveUpButtonPush)			// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimeLineFinishedCallback;
		TimelineProgress.BindDynamic(this, &ADumbwaiter::UpButtonMove);
		LerpTimeLineFinishedCallback.BindUFunction(this, FName("UpButtonPushEndEvent"));
		upButtonPushTimeline.AddInterpFloat(curveUpButtonPush, TimelineProgress);
		upButtonPushTimeline.SetTimelineFinishedFunc(LerpTimeLineFinishedCallback);
		upButtonPushTimeline.SetTimelineLength(1.0f);
	}

	if (curveBottomButtonPush)		// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimeLineFinishedCallback;
		TimelineProgress.BindDynamic(this, &ADumbwaiter::BottomButtonMove);
		LerpTimeLineFinishedCallback.BindUFunction(this, FName("BottomButtonPushEndEvent"));
		bottomButtonPushTimeline.AddInterpFloat(curveBottomButtonPush, TimelineProgress);
		bottomButtonPushTimeline.SetTimelineFinishedFunc(LerpTimeLineFinishedCallback);
		bottomButtonPushTimeline.SetTimelineLength(1.0f);
	}

	buttonTop->startEventDelegate.BindUFunction(this, FName("UpButtonTouch"));

	buttonBottom->startEventDelegate.BindUFunction(this, FName("BottomButtonTouch"));
}

// Called every frame
void ADumbwaiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUpButtonMove)
	{
		upButtonMoveTimer += DeltaTime;

		if (upButtonMoveTimer > 1.0f)
		{
			upButtonMoveTimer = 0.0f;
			bUpButtonMove = false;
		}

		upButtonPushTimeline.TickTimeline(DeltaTime);
	}

	if (bBottomButtonMove)
	{
		bottomButtonMoveTimer += DeltaTime;

		if (bottomButtonMoveTimer > 1.0f)
		{
			bottomButtonMoveTimer = 0.0f;
			bBottomButtonMove = false;

			FoodDelivery();
		}

		bottomButtonPushTimeline.TickTimeline(DeltaTime);
	}

	if (bLeftDoorMove)
	{
		leftDoorMoveTimer += DeltaTime;

		if (leftDoorMoveTimer > 1.0f)
		{
			leftDoorMoveTimer = 0.0f;
			bLeftDoorMove = false;
		}

		leftDoorOpenTimeline.TickTimeline(DeltaTime);
	}

	if (bRightDoorMove)
	{
		rightDoorMoveTimer += DeltaTime;

		if (rightDoorMoveTimer > 1.0f)
		{
			rightDoorMoveTimer = 0.0f;
			bRightDoorMove = false;
		}

		rightDoorOpenTimeline.TickTimeline(DeltaTime);
	}
}

void ADumbwaiter::UpButtonTouch()
{
	upButtonPushTimeline.PlayFromStart();

	leftDoorOpenTimeline.PlayFromStart();
	rightDoorOpenTimeline.PlayFromStart();
		
	bLeftDoorMove = true;
	bRightDoorMove = true;
	bUpButtonMove = true;

	leftDoorMoveTimer = 0.0f;
	rightDoorMoveTimer = 0.0f;
	upButtonMoveTimer = 0.0f;
}

void ADumbwaiter::BottomButtonTouch()
{
	bottomButtonPushTimeline.PlayFromStart();

	leftDoorOpenTimeline.ReverseFromEnd();
	rightDoorOpenTimeline.ReverseFromEnd();
		
	bLeftDoorMove = true;
	bRightDoorMove = true;
	bBottomButtonMove = true;

	leftDoorMoveTimer = 0.0f;
	rightDoorMoveTimer = 0.0f;
	bottomButtonMoveTimer = 0.0f;
}

void ADumbwaiter::LeftDoorMove(float Value)
{
	FRotator newRot(0.0f, Value * 110.f, 0.0f);

	leftDoor->SetRelativeRotation(FRotator(0.0f, Value * 90.f, 0.0f));
}

void ADumbwaiter::RightDoorMove(float Value)
{
	FRotator newRot(0.0f, Value * -110.f, 0.0f);

	RightDoor->SetRelativeRotation(FRotator(0.0f, Value * -90.f, 0.0f));
}

void ADumbwaiter::UpButtonMove(float Value)
{
	FVector newLot(55.5f, 28.1f - (Value * 0.3), -24.3f);

	buttonTop->SetRelativeLocation(newLot);
}

void ADumbwaiter::BottomButtonMove(float Value)
{
	FVector newLot(55.5f, 28.1f - (Value * 0.3), -29.6f);

	buttonBottom->SetRelativeLocation(newLot);
}

void ADumbwaiter::UpButtonPushEndEvent()
{
	upButtonPushTimeline.Reverse();

	bUpButtonMove = true;
	upButtonMoveTimer = 0.0f;
}

void ADumbwaiter::BottomButtonPushEndEvent()
{
	bottomButtonPushTimeline.Reverse();

	bBottomButtonMove = true;
	bottomButtonMoveTimer = 0.0f;
}

void ADumbwaiter::FoodDelivery()
{
	TArray<AActor*> resultCheck;
	resultCheck.Reset();

	boxComp->GetOverlappingActors(resultCheck);

	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();

	if (gm != nullptr)
	{
		FCookingSimulatorRecipeInfo resultRcp = gm->GetCurrentRecipe();
		resultRcp.ingredientInfoArray.Reset();

		for (auto ingredient : resultCheck)
		{
			auto ingredientCheck = Cast<AIngredient>(ingredient);
			if (ingredientCheck != nullptr)
			{
				resultRcp.ingredientInfoArray.Add(ingredientCheck->GetIngredientInfo());
			}
		}

		gm->CompareDeliveryFood(resultRcp);
	}
}

