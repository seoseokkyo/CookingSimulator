// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoButton.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ATwoButton::ATwoButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonBody.ButtonBody'")).Object);

	buttonTop = CreateDefaultSubobject<UInteractComponent>(TEXT("Button Top"));
	buttonTop->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonTop.ButtonTop'")).Object);
	buttonTop->SetupAttachment(baseMesh);
	buttonTop->SetRelativeLocation(FVector(1.0f, 0.0f, 2.7f));

	buttonBottom = CreateDefaultSubobject<UInteractComponent>(TEXT("Button Bottom"));
	buttonBottom->SetupAttachment(baseMesh);
	buttonBottom->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonBottom.ButtonBottom'")).Object);
	buttonBottom->SetRelativeLocation(FVector(1.0f, 0.0f, -2.6f));
}

// Called when the game starts or when spawned
void ATwoButton::BeginPlay()
{
	Super::BeginPlay();

	if (curveUpButtonPush)			// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimeLineFinishedCallback;
		TimelineProgress.BindDynamic(this, &ATwoButton::UpButtonMove);
		LerpTimeLineFinishedCallback.BindUFunction(this, FName("UpButtonPushEndEvent"));
		upButtonPushTimeline.AddInterpFloat(curveUpButtonPush, TimelineProgress);
		upButtonPushTimeline.SetTimelineFinishedFunc(LerpTimeLineFinishedCallback);
	}

	if (curveBottomButtonPush)		// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimeLineFinishedCallback;
		TimelineProgress.BindDynamic(this, &ATwoButton::BottomButtonMove);
		LerpTimeLineFinishedCallback.BindUFunction(this, FName("BottomButtonPushEndEvent"));
		bottomButtonPushTimeline.AddInterpFloat(curveBottomButtonPush, TimelineProgress);
		bottomButtonPushTimeline.SetTimelineFinishedFunc(LerpTimeLineFinishedCallback);
	}

	buttonTop->startEventDelegate.BindUFunction(this, FName("UpButtonTouch"));
	
	buttonBottom->startEventDelegate.BindUFunction(this, FName("BottomButtonTouch"));
}

// Called every frame
void ATwoButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	upButtonPushTimeline.TickTimeline(DeltaTime);
	bottomButtonPushTimeline.TickTimeline(DeltaTime);
}

void ATwoButton::UpButtonTouch()
{
	upButtonPushTimeline.PlayFromStart();
}

void ATwoButton::BottomButtonTouch()
{
	bottomButtonPushTimeline.PlayFromStart();
}

void ATwoButton::UpButtonMove(float Value)
{
	FVector newLoc(1.0f - (Value * 0.3), 0.0f, 2.7f);
	buttonTop->SetRelativeLocation(newLoc);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("buttonTop X : %.03f"), newLoc.X));
}

void ATwoButton::BottomButtonMove(float Value)
{
	buttonBottom->SetRelativeLocation(FVector(1.0f - (Value * 0.3), 0.0f, -2.6f));
}

void ATwoButton::UpButtonPushEndEvent()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("UpButtonPushEndEvent() Call"));
	//upButtonPushTimeline.ReverseFromEnd();
	upButtonPushTimeline.Reverse();
}

void ATwoButton::BottomButtonPushEndEvent()
{
	//bottomButtonPushTimeline.ReverseFromEnd();
	bottomButtonPushTimeline.Reverse();
}
