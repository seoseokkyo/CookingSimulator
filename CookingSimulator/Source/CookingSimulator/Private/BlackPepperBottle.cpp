// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackPepperBottle.h"
#include "TestCharacter.h"
#include <Components/SplineMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Materials/MaterialInterface.h>
#include <BlackPepper.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
ABlackPepperBottle::ABlackPepperBottle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	toolType = ECookingToolType::SaucePouch;

	ItemName = TEXT("BlackPepperBottle");
}

// Called when the game starts or when spawned
void ABlackPepperBottle::BeginPlay()
{
	Super::BeginPlay();

	splinePositions.Reset();

	auto playerCharacter = Cast<ATestCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerCharacter != nullptr)
	{
		playerCharacter->hitPointDelegate.BindUFunction(this, FName("OnAddNewPosition"));
	}


	if (blackPepperActor_BP != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//ketchupActor = CreateDefaultSubobject<AKetchup>(TEXT("Ketchup"));
		blackPepperActor = GetWorld()->SpawnActor<ABlackPepper>(blackPepperActor_BP, FTransform(GetActorRotation(), GetActorLocation(), GetActorScale()), param);
		blackPepperActor->SetActorLocation(GetActorLocation());
	}
}

// Called every frame
void ABlackPepperBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (bTargetOn)
	//{
	//	RotationToTarget();
	//}

	if (bStart)
	{
		delayTime += DeltaTime;

		if (delayTime > 0.5)
		{
			delayTime = 0.0f;

			FCollisionQueryParams params;
			params.AddIgnoredActor(this);
			params.AddIgnoredActor(this->GetOwner());
			params.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());

			FHitResult hitResult;
			FVector start = GetActorLocation();
			FVector end = start + GetActorUpVector() * 500;

			for (int i = 0; i < 6; i++)
			{
				int32 randX = FMath::RandRange(0, 10);
				int32 randY = FMath::RandRange(-10, 0);

				start.X += randX;
				start.Y += randY;

				end.X += randX;
				end.Y += randY;

				GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params);

				//auto blackPepperCheck = Cast<ABlackPepper>(hitResult.GetActor());

				OnAddNewPosition(hitResult.ImpactPoint, hitResult);
			}
		}
	}
}

void ABlackPepperBottle::OnAddNewPosition(FVector newPos, FHitResult& hitResult)
{
	splinePositions.Add(newPos);

	int32 posSize = splinePositions.Num();

	FName splineName(FString::Printf(TEXT("MySalt%03d"), splinePositions.Num()));

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto newBlackPepper = GetWorld()->SpawnActor<ABlackPepper>(blackPepperActor_BP, FTransform(FRotator::ZeroRotator, hitResult.ImpactPoint, FVector(1, 1, 1)), spawnParam);

	newBlackPepper->SetActorLocation(newPos);
	newBlackPepper->AttachToActor(hitResult.GetActor(), FAttachmentTransformRules::KeepWorldTransform);

	//USplineMeshComponent* SplineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
	newBlackPepper->baseMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), splineName);
	newBlackPepper->baseMesh->SetMobility(EComponentMobility::Movable);

	if (newBlackPepper->baseMesh != nullptr)
	{
		newBlackPepper->baseMesh->RegisterComponent();

		newBlackPepper->AttachToComponent(hitResult.GetComponent(), FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ABlackPepperBottle::SetTargetPoint(FVector _targetPoint)
{
	targetPoint = _targetPoint;
	bTargetOn = true;
}

void ABlackPepperBottle::ReleaseTargetPoint()
{
	targetPoint = FVector::ZeroVector;
	bTargetOn = false;
}

void ABlackPepperBottle::RotationToTarget()
{
	//FVector dir = targetPoint - GetActorLocation();
	FVector target(413.0f, 71.0f, 92.0f);

	FVector dir = target - GetActorLocation();
	dir.Normalize();
	UKismetMathLibrary::MakeRotFromZY(GetActorForwardVector(), GetActorUpVector());



	SetActorRotation(dir.Rotation());
}

