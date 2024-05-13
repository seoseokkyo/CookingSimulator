


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
#include "LineDecalActor.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include "CookingSimulatorGameModeBase.h"
#include "InteractComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>


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

	// �����տ� �� ����ƽ�޽�������Ʈ
	GripItemRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripRightItem"));
	GripItemRight->SetupAttachment(MotionRight);
	GripItemRight->SetVisibility(false);

	// �޼տ� �� ����ƽ�޽�������Ʈ
	GripItemLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripLeftItem"));
	GripItemLeft->SetupAttachment(MotionLeft);
	GripItemLeft->SetVisibility(false);

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

	if (redDotDecal_inst == nullptr)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		redDotDecal_inst = GetWorld()->SpawnActor<APointDecalActor>(PointDecalActor, FVector(0, 0, -50000), FRotator::ZeroRotator, params);
	}
		
	if (lineDecal_inst == nullptr)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		lineDecal_inst = GetWorld()->SpawnActor<ALineDecalActor>(LineDecalActor, FVector(0, 0, -50000), FRotator::ZeroRotator, params);
		//lineDecal_inst->SetActorScale3D(FVector(5));
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
	FVector start = MeshRight->GetComponentLocation();
	FVector end = start + MeshRight->GetRightVector() * 100000;

	// �ƿ����� �� �����ϴ��� Ȯ�ο� �� �׸���
	DrawLine(start, end);

	// �ε�ģ ����� ��ȣ�ۿ� ������ ���Ͷ�� �ܰ��� �������� �Ѵ�
	// RenderCustomDepth ���
	CheckHitTraceForOutline(start, end);


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

		input->BindAction(IA_MyGripR, ETriggerEvent::Triggered, this, &ATestCharacter::OnIAGripR);
		input->BindAction(IA_MyGripR, ETriggerEvent::Completed, this, &ATestCharacter::OnIAUnGripR);

		input->BindAction(IA_MyGripL, ETriggerEvent::Triggered, this, &ATestCharacter::OnIAGripL);
		input->BindAction(IA_MyGripL, ETriggerEvent::Completed, this, &ATestCharacter::OnIAUnGripL);
	}

	// ���߿� ���� �ذ�Ǹ� ���� ����
	//BeginPlay();
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
void ATestCharacter::OnIAGripR(const FInputActionValue& value)
{
	FVector startPos = MotionRight->GetComponentLocation();
	FVector endPos = startPos + MotionRight->GetUpVector() * -100000;

	FHitResult hitInfo;	// �ε��� ���
	// bool bHit = HitTest(startPos, endPos, hitInfo);

	TArray<FOverlapResult> hits;
	FVector origin = MotionRight->GetComponentLocation();
	FQuat rot = FQuat::Identity;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredComponent(MeshRight);
	params.AddIgnoredComponent(MeshLeft);

	bool bHit = HitTest(startPos, endPos, hitInfo);

	// ���� ����Ȱ��� �ִٸ�
	if (bHit)
	{
		if (bCanGrip)
		{
			// �ش� �������� ���
			GripItem(GripActor);
		}
	}
	
	// �ұ�/���� ���� �� ������ ����Ʈ ��ġ�� ��´� 
	FVector grabLoc = MotionRight->GetComponentLocation();
	FVector dropLoc = grabLoc + FVector(0, 0, -1) * 1000;
	// FVector dropLoc = grabLoc * FVector(1, 1, 0);

	// ������ ����Ʈ �� �۵��ϴ��� Ȯ�ο� �� �׸���
	DrawLine(grabLoc, dropLoc);

	// ���� �ұ� �ø����� �� �ҽ��� ����ִٸ� 
	//if (bGripSauce)
	{
		// �������� ������ ������ ����Ʈ ǥ��
		CheckHitTraceForLaserPointer(grabLoc, dropLoc);
	}

	// Į �� ���� ������ ����ִٸ�
	// if (bGripCookingTool)
	{
		// �ڸ� ������ ���� ǥ��
		CheckHitTraceForDottedLine(grabLoc, dropLoc);
	}
}

void ATestCharacter::OnIAUnGripR(const FInputActionValue& value)
{
	MeshRight->SetVisibility(true);
	//GripActor->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GripActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//GripActor->SetSimulatePhysics(true);
	GripActor->baseMesh->SetSimulatePhysics(true);


	if (redDotDecal_inst != nullptr)
	{
		redDotDecal_inst->SetShowDecal(false);
	}
	if (lineDecal_inst != nullptr)
	{
		lineDecal_inst->SetShowDecal(false);
	}
	
}

void ATestCharacter::OnIAGripL(const FInputActionValue& value)
{
}

void ATestCharacter::OnIAUnGripL(const FInputActionValue& value)
{
}

void ATestCharacter::GripItem(AItem* item)
{

	// ���� �� �޽ø� ���ְ�
	MeshRight->SetVisibility(false);
	// ���� �������� ��ġ��Ŵ
	//item->SetSimulatePhysics(false);
	//item->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	item->AttachToComponent(MotionRight, FAttachmentTransformRules::KeepWorldTransform);
	if (item != nullptr)
	{
		//item->SetActorEnableCollision(ECollisionEnabled::NoCollision);
		//item->baseMesh->SetSimulatePhysics(false);

		item->SetActorRelativeLocation(MotionRight->GetComponentLocation());
		
		// item->IgnoreComponentWhenMoving(GetCapsuleComponent(), true);

		IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
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

			// ���⿡�ٰ��� ���°� �³�
			bCanGrip = false;
		}

		if (item != nullptr)
		{
			focusedActor = interactedActor;

			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, true);
			GripActor = Cast<AItem>(focusedActor);
			bCanGrip = true;
		}

	}
	else
	{
		if (focusedActor != nullptr)
		{
			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
			focusedActor = nullptr;
			targetComp = nullptr;
			
			bCanGrip = false;
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

void ATestCharacter::CheckHitTraceForDottedLine(const FVector& startPos, FVector& endPos)
{
	FHitResult hitInfo;
	bool bHit = HitTest(startPos, endPos, hitInfo);
	FVector dropPoint = hitInfo.ImpactPoint;

	if (bHit)
	{

		if (lineDecal_inst != nullptr)
		{
			lineDecal_inst->SetActorLocation(dropPoint);
			lineDecal_inst->SetShowDecal(true);
		}
	}
	else
	{
		if (lineDecal_inst != nullptr)
		{
			lineDecal_inst->SetShowDecal(false);
		}
	}
}

void ATestCharacter::DrawLine(FVector start, FVector end)
{
	// throw std::logic_error("The method or operation is not implemented.");

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0, 0, 0.5f);
}

bool ATestCharacter::HitTest(FVector start, FVector end, FHitResult& outHit)
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);
}

