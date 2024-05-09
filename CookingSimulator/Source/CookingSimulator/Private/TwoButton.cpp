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

	buttonTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Top"));
	buttonTop->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/CookingSimulator/Blueprints/CookingTools/Mesh/Switch/ButtonTop.ButtonTop'")).Object);
	buttonTop->SetupAttachment(baseMesh);
	buttonTop->SetRelativeLocation(FVector(1.0f, 0.0f, 2.7f));

	buttonBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Bottom"));
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
	}

	if (curveBottomButtonPush)		// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimeLineFinishedCallback;
		TimelineProgress.BindDynamic(this, &ATwoButton::BottomButtonMove);
		LerpTimeLineFinishedCallback.BindUFunction(this, FName("BottomButtonPushEndEvent"));
		bottomButtonPushTimeline.AddInterpFloat(curveBottomButtonPush, TimelineProgress);
	}

	//buttonTop->OnInputTouchEnter.AddDynamic(this, &ATwoButton::UpButtonTouch);
	buttonTop->OnClicked.AddDynamic(this, &ATwoButton::UpButtonTouch);
	buttonTop->OnComponentBeginOverlap.AddDynamic(this, &ATwoButton::OnOverlapUpButton);

	//buttonBottom->OnInputTouchEnter.AddDynamic(this, &ATwoButton::BottomButtonTouch);
	buttonBottom->OnClicked.AddDynamic(this, &ATwoButton::BottomButtonTouch);
	buttonBottom->OnComponentBeginOverlap.AddDynamic(this, &ATwoButton::OnOverlapBottomButton);
}

// Called every frame
void ATwoButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	upButtonPushTimeline.TickTimeline(DeltaTime);
	bottomButtonPushTimeline.TickTimeline(DeltaTime);
}

void ATwoButton::UpButtonTouch(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString(L"UpButtonTouched"));

	upButtonPushTimeline.PlayFromStart();
}

void ATwoButton::OnOverlapUpButton(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString(L"OnOverlapUpButton"));
}

void ATwoButton::BottomButtonTouch(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString(L"BottomButtonTouch"));

	bottomButtonPushTimeline.PlayFromStart();
}

void ATwoButton::OnOverlapBottomButton(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString(L"OnOverlapBottomButton"));
}

void ATwoButton::UpButtonMove(float Value)
{
	buttonTop->SetRelativeLocation(FVector(Value * -0.5, 0, 0));
}

void ATwoButton::BottomButtonMove(float Value)
{
	buttonBottom->SetRelativeLocation(FVector(Value * -0.5, 0, 0));
}

void ATwoButton::UpButtonPushEndEvent()
{
	upButtonPushTimeline.ReverseFromEnd();
}

void ATwoButton::BottomButtonPushEndEvent()
{
	bottomButtonPushTimeline.ReverseFromEnd();
}
