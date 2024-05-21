// Fill out your copyright notice in the Description page of Project Settings.


#include "SaltBottle.h"
#include "TestCharacter.h"
#include <Components/SplineMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Materials/MaterialInterface.h>
#include <Salt.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>

// Sets default values
ASaltBottle::ASaltBottle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	toolType = ECookingToolType::SaucePouch;

	ItemName = TEXT("SaltBottle");

	soundComp_Salt = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Comp"));
	soundComp_Salt->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASaltBottle::BeginPlay()
{
	Super::BeginPlay();

	soundComp_Salt->Stop();

	splinePositions.Reset();

	auto playerCharacter = Cast<ATestCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerCharacter != nullptr)
	{
		playerCharacter->hitPointDelegate.BindUFunction(this, FName("OnAddNewPosition"));
	}


	if (saltActor_BP != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//ketchupActor = CreateDefaultSubobject<AKetchup>(TEXT("Ketchup"));
		saltActor = GetWorld()->SpawnActor<ASalt>(saltActor_BP, FTransform(GetActorRotation(), GetActorLocation(), GetActorScale()), param);
		saltActor->SetActorLocation(GetActorLocation());
	}
}

// Called every frame
void ASaltBottle::Tick(float DeltaTime)
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
			if (soundComp_Salt != nullptr)
			{
				soundComp_Salt->Stop();
				soundComp_Salt->Play();
			}

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
				int32 randX = FMath::RandRange(-5, 5);
				int32 randY = FMath::RandRange(-5, 5);

				start.X += randX;
				start.Y += randY;

				end.X += randX;
				end.Y += randY;

				GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params);

				//auto saltCheck = Cast<ASalt>(hitResult.GetActor());

				OnAddNewPosition(hitResult.ImpactPoint, hitResult);
			}
		}
	}
}

void ASaltBottle::OnAddNewPosition(FVector newPos, FHitResult& hitResult)
{
	splinePositions.Add(newPos);

	int32 posSize = splinePositions.Num();

	FName splineName(FString::Printf(TEXT("MySalt%03d"), splinePositions.Num()));

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto newSalt = GetWorld()->SpawnActor<ASalt>(saltActor_BP, FTransform(FRotator::ZeroRotator, hitResult.ImpactPoint, FVector(1, 1, 1)), spawnParam);

	newSalt->SetActorLocation(newPos);
	newSalt->AttachToActor(hitResult.GetActor(), FAttachmentTransformRules::KeepWorldTransform);

	//USplineMeshComponent* SplineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
	newSalt->baseMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), splineName);
	newSalt->baseMesh->SetMobility(EComponentMobility::Movable);

	if (newSalt->baseMesh != nullptr)
	{
		newSalt->baseMesh->RegisterComponent();

		newSalt->AttachToComponent(hitResult.GetComponent(), FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ASaltBottle::SetTargetPoint(FVector _targetPoint)
{
	targetPoint = _targetPoint;
	bTargetOn = true;
}

void ASaltBottle::ReleaseTargetPoint()
{
	targetPoint = FVector::ZeroVector;
	bTargetOn = false;
}

void ASaltBottle::RotationToTarget()
{
	//FVector dir = targetPoint - GetActorLocation();
	FVector target(413.0f, 71.0f, 92.0f);

	FVector dir = target - GetActorLocation();
	dir.Normalize();
	UKismetMathLibrary::MakeRotFromZY(GetActorForwardVector(), GetActorUpVector());



	SetActorRotation(dir.Rotation());
}


