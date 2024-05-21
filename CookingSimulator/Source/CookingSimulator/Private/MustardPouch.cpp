// Fill out your copyright notice in the Description page of Project Settings.


#include "MustardPouch.h"
#include "TestCharacter.h"
#include <Components/SplineMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Materials/MaterialInterface.h>
#include <Mustard.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>


// Sets default values
AMustardPouch::AMustardPouch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	toolType = ECookingToolType::SaucePouch;

	ItemName = TEXT("MustardPouch");

	soundComp_Mustard = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Comp"));
	soundComp_Mustard->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMustardPouch::BeginPlay()
{
	Super::BeginPlay();

	splinePositions.Reset();
	splineMeshs.Reset();

	auto playerCharacter = Cast<ATestCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerCharacter != nullptr)
	{
		playerCharacter->hitPointDelegate.BindUFunction(this, FName("OnAddNewPosition"));
	}


	if (mustardActor_BP != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//ketchupActor = CreateDefaultSubobject<AKetchup>(TEXT("Ketchup"));
		mustardActor = GetWorld()->SpawnActor<AMustard>(mustardActor_BP, FTransform(GetActorRotation(), GetActorLocation(), GetActorScale()), param);
		mustardActor->SetActorLocation(GetActorLocation());
	}
}

// Called every frame
void AMustardPouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		delayTime += DeltaTime;

		if (delayTime > 0.1)
		{
			if (soundComp_Mustard != nullptr)
			{
				soundComp_Mustard->Stop();
				soundComp_Mustard->Play();
			}

			delayTime = 0.0f;

			FCollisionQueryParams params;
			params.AddIgnoredActor(this);
			params.AddIgnoredActor(this->GetOwner());
			params.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());

			FHitResult hitResult;
			FVector start = GetActorLocation();
			FVector end = start + GetActorUpVector() * 500;

			GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params);

			auto mustardCheck = Cast<AMustard>(hitResult.GetActor());

			OnAddNewPosition(hitResult.ImpactPoint, hitResult);
		}
	}
}


void AMustardPouch::OnAddNewPosition(FVector newPos, FHitResult& hitResult)
{
	splinePositions.Add(newPos);

	int32 posSize = splinePositions.Num();

	if (posSize > 1)
	{
		if (FVector::Dist(splinePositions[posSize - 2], splinePositions[posSize - 1]) > 100)
		{
			splinePositions.Pop(false);
			splinePositions.Pop(false);
			return;
		}

		FName splineName(FString::Printf(TEXT("MySpline%03d"), splinePositions.Num()));

		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto newMustard = GetWorld()->SpawnActor<AMustard>(mustardActor_BP, FTransform(FRotator::ZeroRotator, hitResult.ImpactPoint, FVector(1, 1, 1)), spawnParam);

		newMustard->SetActorLocation(newPos);
		newMustard->AttachToActor(hitResult.GetActor(), FAttachmentTransformRules::KeepWorldTransform);

		//USplineMeshComponent* SplineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
		newMustard->splineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
		newMustard->splineComp->SetMobility(EComponentMobility::Movable);

		if (newMustard->splineComp != nullptr)
		{
			splineMeshs.Add(newMustard->splineComp);

			for (const auto& mesh : splineMeshs)
			{
				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("P : %p, L : %d"), mesh, splineMeshs.Num()));
			}

			newMustard->baseMesh->SetMaterial(0, splineMaterial);
			newMustard->splineComp->SetMaterial(0, splineMaterial);

			if (newMustard->splineComp != nullptr)
			{
				newMustard->splineComp->SetStaticMesh(newMustard->splineMesh);

				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("SplineComp : %p"), newMustard->splineMesh));
			}

			newMustard->splineComp->RegisterComponent();

			newMustard->splineComp->SetForwardAxis(ESplineMeshAxis::X);

			newMustard->splineComp->SetStartPosition(splinePositions[posSize - 2], false);
			newMustard->splineComp->SetEndPosition(splinePositions[posSize - 1], true);

			newMustard->splineComp->AttachToComponent(hitResult.GetComponent(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AMustardPouch::SetTargetPoint(FVector _targetPoint)
{
	targetPoint = _targetPoint;
	bTargetOn = true;
}

void AMustardPouch::ReleaseTargetPoint()
{
	targetPoint = FVector::ZeroVector;
	bTargetOn = false;
}

void AMustardPouch::RotationToTarget()
{
	//FVector dir = targetPoint - GetActorLocation();
	FVector target(413.0f, 71.0f, 92.0f);

	FVector dir = target - GetActorLocation();
	dir.Normalize();
	UKismetMathLibrary::MakeRotFromZY(GetActorForwardVector(), GetActorUpVector());



	SetActorRotation(dir.Rotation());
}


