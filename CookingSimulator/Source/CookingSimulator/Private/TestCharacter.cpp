


// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCharacter.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine/SkeletalMesh.h>
#include <Animation/AnimInstance.h>
#include <Engine/LocalPlayer.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>
#include <Components/CapsuleComponent.h>
#include <item.h>
#include "PointDecalActor.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include "CookingSimulatorGameModeBase.h"
#include "InteractComponent.h"


// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	MotionRight=CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionRight"));
	MotionRight->SetTrackingMotionSource("Right");
	MotionRight->SetupAttachment(RootComponent);
	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionLeft"));
	MotionLeft->SetTrackingMotionSource("Left");
	MotionLeft->SetupAttachment(RootComponent);

	MeshRight=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshRight"));
	MeshRight->SetupAttachment(MotionRight);
	MeshLeft=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshLeft"));
	MeshLeft->SetupAttachment(MotionLeft);

	// ������ ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMeshRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (TempMeshRight.Succeeded())
	{
		MeshRight->SetSkeletalMesh(TempMeshRight.Object);
		MeshRight->SetWorldLocationAndRotation(FVector(-3.0f, 3.5f, 4.5f), FRotator(25.0f, 0.0f, 90.0f));
	}

	// �޼� ����
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
	
	//pc = GetController<APlayerController>();
	pc = Cast<APlayerController>(GetController());

	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		
		if (subsys)
		{
			subsys->AddMappingContext(IMC_Player, 0);
		}
	}

	// ������ ����Ʈ ��Į
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (redDotDecal_inst == nullptr)
	{
		redDotDecal_inst = GetWorld()->SpawnActor<APointDecalActor>(myDecalActor, GetActorLocation(), FRotator::ZeroRotator, params);
		redDotDecal_inst->SetActorScale3D(FVector(0.03f));
	}	
	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		gm->SetCurrentRecipe(ECookingSimulatorRecipeType::Hamburger);
	}
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �÷��� �߿��� �׻� �޼�(���̷�Ż�޽�)���� Ʈ���̽��� ����ȴ�
	FVector start = MeshLeft->GetComponentLocation();
	FVector end = start + MeshLeft->GetRightVector() * 100000;

	// �ƿ����� �� �����ϴ��� Ȯ�ο� �� �׸���
	DrawLine(start,end);

	// �ε�ģ ����� ��ȣ�ۿ� ������ ���Ͷ�� �ܰ��� �������� �Ѵ�
	// RenderCustomDepth ���
	CheckHitTraceForOutline(start, end);
	
	// �ұ�/���� ���� �� ������ ����Ʈ ��ġ�� ��´� 
	FVector grabLoc = MeshRight->GetComponentLocation();
	// FVector dropLoc = grabLoc + MeshRight->GetForwardVector() * -1000;
	FVector dropLoc = grabLoc * FVector(1, 1, 0);

	// ������ ����Ʈ �� �۵��ϴ��� Ȯ�ο� �� �׸���
	DrawLine(grabLoc, dropLoc);

	//myDecalActor->(GetActorLocation());
	CheckHitTraceForLaserPointer(grabLoc, dropLoc);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATestCharacter::OnIAMove);
		input->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATestCharacter::OnIATurn);
		input->BindAction(IA_Trigger, ETriggerEvent::Started, this, &ATestCharacter::OnIATrigger);
	}

	// ���߿� ���� �ذ�Ǹ� ���� ����
	BeginPlay();
}

void ATestCharacter::OnIAMove(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), v.X);
	AddMovementInput(GetActorRightVector(), v.Y);
}

void ATestCharacter::OnIATurn(const FInputActionValue& value)
{
	AddControllerYawInput(value.Get<float>());
}

void ATestCharacter::OnIATrigger(const FInputActionValue& value)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%p"), targetComp));
	if (targetComp != nullptr)
	{
		IInteractAbleInterface::Execute_InteractStart(targetComp);
	}
}

void ATestCharacter::CheckHitTraceForOutline(const FVector& startPos, FVector& endPos)
{
	// lineTrace�� �ؼ� �ε��� ���Ͱ� �ִٸ� ���� �ƿ����� �����ǵ��� �Ӹ�Ƽ�� ���¸� �����Ѵ�
	FHitResult hitInfo;	// �ε��� ���
	bool bHit = HitTest(startPos, endPos, hitInfo);
	
	AActor* interactedActor = hitInfo.GetActor();

	UInteractComponent* compCheck = Cast<UInteractComponent>(hitInfo.GetComponent());
	if (compCheck != nullptr)
	{
		targetComp = compCheck;
	}

	if (bHit)
	{
		// �ε��� ������ Render CustomDepthPass�� true�� �����Ѵ�
		// Cast<AItem>(interactedActor)->baseMesh->SetCustomDepthStencilValue();
		auto item = Cast<IInteractAbleInterface>(interactedActor);

		if (focusedActor != nullptr && interactedActor != focusedActor)
		{
			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
			focusedActor = nullptr;
			targetComp = nullptr;
		}

		if (item != nullptr)
		{
			focusedActor = interactedActor;

			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, true);
		}		
	}
	else
	{
		if (focusedActor != nullptr)
		{
			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
			focusedActor = nullptr;
			targetComp = nullptr;
		}
	}
}

void ATestCharacter::CheckHitTraceForLaserPointer(const FVector& startPos, FVector& endPos)
{
	FHitResult hitInfo;
	bool bHit = HitTest(startPos, endPos, hitInfo);

	FVector dropPoint = hitInfo.ImpactPoint;

	if (bHit)
	{
		if (redDotDecal_inst != nullptr)
		{
			redDotDecal_inst->SetActorLocation(dropPoint);

			redDotDecal_inst->SetShowDecal(true);
		}
	}
	else 
	{
		if (redDotDecal_inst != nullptr)
		{
			redDotDecal_inst->SetShowDecal(false);
		}
	}
}

void ATestCharacter::ShowDropPoint(const FVector& start, const FVector& end)
{
}

void ATestCharacter::DrawLine(FVector start, FVector end)
{
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1.0f, 0, 0.5f);
}

bool ATestCharacter::HitTest(FVector start, FVector end, FHitResult& outHit)
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);
}

