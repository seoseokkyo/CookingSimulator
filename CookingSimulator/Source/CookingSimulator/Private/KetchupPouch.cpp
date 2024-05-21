// Fill out your copyright notice in the Description page of Project Settings.


#include "KetchupPouch.h"
#include "TestCharacter.h"
#include <Components/SplineMeshComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Materials/MaterialInterface.h>
#include <Ketchup.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>

// Sets default values
AKetchupPouch::AKetchupPouch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	toolType = ECookingToolType::SaucePouch;

	ItemName = TEXT("KetchupPouch");

	soundComp_Ketchup = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Comp"));
	soundComp_Ketchup->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKetchupPouch::BeginPlay()
{
	Super::BeginPlay();

	soundComp_Ketchup->Stop();

	splinePositions.Reset();
	splineMeshs.Reset();

	auto playerCharacter = Cast<ATestCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerCharacter != nullptr)
	{
		playerCharacter->hitPointDelegate.BindUFunction(this, FName("OnAddNewPosition"));
	}


	if (ketchupActor_BP != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//ketchupActor = CreateDefaultSubobject<AKetchup>(TEXT("Ketchup"));
		ketchupActor = GetWorld()->SpawnActor<AKetchup>(ketchupActor_BP, FTransform(GetActorRotation(), GetActorLocation(), GetActorScale()), param);
		ketchupActor->SetActorLocation(GetActorLocation());
	}
}

// Called every frame
void AKetchupPouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (bTargetOn)
	//{
	//	RotationToTarget();
	//}

	if (bStart)
	{
		delayTime += DeltaTime;

		if (delayTime > 0.1)
		{
			if (soundComp_Ketchup != nullptr)
			{
				soundComp_Ketchup->Stop();
				soundComp_Ketchup->Play();
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

			auto ketchupCheck = Cast<AKetchup>(hitResult.GetActor());

			OnAddNewPosition(hitResult.ImpactPoint, hitResult);
		}
	}
}

void AKetchupPouch::OnAddNewPosition(FVector newPos, FHitResult& hitResult)
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

		auto newKetchup = GetWorld()->SpawnActor<AKetchup>(ketchupActor_BP, FTransform(FRotator::ZeroRotator, hitResult.ImpactPoint, FVector(1, 1, 1)), spawnParam);

		newKetchup->SetActorLocation(newPos);
		newKetchup->AttachToActor(hitResult.GetActor(), FAttachmentTransformRules::KeepWorldTransform);

		//USplineMeshComponent* SplineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
		newKetchup->splineComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), splineName);
		newKetchup->splineComp->SetMobility(EComponentMobility::Movable);

		if (newKetchup->splineComp != nullptr)
		{
			splineMeshs.Add(newKetchup->splineComp);

			for (const auto& mesh : splineMeshs)
			{
				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("P : %p, L : %d"), mesh, splineMeshs.Num()));
			}

			newKetchup->baseMesh->SetMaterial(0, splineMaterial);
			newKetchup->splineComp->SetMaterial(0, splineMaterial);

			if (newKetchup->splineComp != nullptr)
			{
				newKetchup->splineComp->SetStaticMesh(newKetchup->splineMesh);

				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("SplineComp : %p"), newKetchup->splineMesh));
			}

			newKetchup->splineComp->RegisterComponent();

			newKetchup->splineComp->SetForwardAxis(ESplineMeshAxis::X);

			newKetchup->splineComp->SetStartPosition(splinePositions[posSize - 2], false);
			newKetchup->splineComp->SetEndPosition(splinePositions[posSize - 1], true);

			newKetchup->splineComp->AttachToComponent(hitResult.GetComponent(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AKetchupPouch::SetTargetPoint(FVector _targetPoint)
{
	targetPoint = _targetPoint;
	bTargetOn = true;
}

void AKetchupPouch::ReleaseTargetPoint()
{
	targetPoint = FVector::ZeroVector;
	bTargetOn = false;
}

void AKetchupPouch::RotationToTarget()
{
	//FVector dir = targetPoint - GetActorLocation();
	FVector target(413.0f, 71.0f, 92.0f);

	FVector dir = target - GetActorLocation();
	dir.Normalize();
	UKismetMathLibrary::MakeRotFromZY(GetActorForwardVector(), GetActorUpVector());



	SetActorRotation(dir.Rotation());
}

