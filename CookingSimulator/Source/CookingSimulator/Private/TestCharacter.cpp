// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>


// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	MotionRight=CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionRight"));
	MotionRight->SetupAttachment(RootComponent);
	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionLeft"));
	MotionLeft->SetupAttachment(RootComponent);

	MeshRight=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshRight"));
	MeshRight->SetupAttachment(MotionRight);
	MeshLeft=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshLeft"));
	MeshLeft->SetupAttachment(MotionLeft);

	// 오른손 세팅
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMeshRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (TempMeshRight.Succeeded())
	{
		MeshRight->SetSkeletalMesh(TempMeshRight.Object);
		MeshRight->SetWorldLocationAndRotation(FVector(-3.0f, 3.5f, 4.5f), FRotator(25.0f, 0.0f, 90.0f));
	}

	// 왼손 세팅
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMeshLeft(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
	if (TempMeshLeft.Succeeded())
	{
		MeshLeft->SetSkeletalMesh(TempMeshLeft.Object);
		MeshLeft->SetWorldLocationAndRotation(FVector(-3.0f, -3.5f, 4.5f), FRotator(-25.0f, -180.0f, 90.0f));
	}



}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	pc = GetController<APlayerController>();

	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		
		if (subsys)
		{
			subsys->AddMappingContext(IMC_TestPlayer, 0);
		}
	}


}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플레이 중에는 항상 왼손(스켈레탈메시)에서 트레이싱이 진행된다
	FVector start = MeshLeft->GetComponentLocation();
	FVector end = start + MeshLeft->GetRightVector() * 100000;

	// 잘 동작하는지 확인용 선 그리기
	DrawLine(start,end);

	// lineTrace를 해서 부딪힌 액터가 있다면 액터 아웃라인 강조되도록 머리티얼 상태를 변경한다
	FHitResult hitInfo;	// 부딪힌 대상
	bool bHit = HitTest(start, end, hitInfo);

	if (bHit)
	{
		// 부딪힌 액터의 Render CustomDepthPass를 true로 변경한다
		AActor* interactedActor = hitInfo.GetActor();
		
	}
	else
	{
		// 부딪힌 액터의 Render CustomDepthPass를 false로 변경한다

	}


}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestCharacter::DrawLine(FVector start, FVector end)
{
	// throw std::logic_error("The method or operation is not implemented.");

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1.0f, 0, 0.5f);
}

bool ATestCharacter::HitTest(FVector start, FVector end, FHitResult& outHit)
{
	// throw std::logic_error("The method or operation is not implemented.");

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);
}

