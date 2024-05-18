


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
#include "Dumbwaiter.h"
#include "ProceduralMeshComponent.h"


// Sets default values
ATestCharacter::ATestCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	MotionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionRight"));
	MotionRight->SetTrackingMotionSource("Right");
	MotionRight->SetupAttachment(RootComponent);
	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionLeft"));
	MotionLeft->SetTrackingMotionSource("Left");
	MotionLeft->SetupAttachment(RootComponent);

	MeshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshRight"));
	MeshRight->SetupAttachment(MotionRight);
	MeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshLeft"));
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
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		redDotDecal_inst = GetWorld()->SpawnActor<APointDecalActor>(PointDecalActor, FVector(0, 0, -50000), FRotator::ZeroRotator, spawnParams);
	}

	if (lineDecal_inst == nullptr)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		lineDecal_inst = GetWorld()->SpawnActor<ALineDecalActor>(LineDecalActor, FVector(0, 0, -50000), FRotator::ZeroRotator, spawnParams);
		//lineDecal_inst->SetActorScale3D(FVector(5));
	}

	ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();
	if (gm != nullptr)
	{
		gm->SetCurrentRecipe(ECookingSimulatorRecipeType::Hamburger);
	}

	params.AddIgnoredActor(this);

	params.AddIgnoredComponent(MeshLeft);
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// �÷��� �߿��� �׻� �޼�(���̷�Ż�޽�)���� Ʈ���̽��� ����ȴ�
	FVector start = MeshRight->GetComponentLocation();
	FVector end = start + MeshRight->GetRightVector() * 100000;


	// �ε�ģ ����� ��ȣ�ۿ� ������ ���Ͷ�� �ܰ��� �������� �Ѵ�
	// RenderCustomDepth ���
	if (bCanTrace)
	{
		// �ƿ����� �� �����ϴ��� Ȯ�ο� �� �׸���
		DrawLine(start, end);

		CheckHitTraceForOutline(start, end);
	}


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
	AddMovementInput(GetActorRightVector(), v.Y * -1.f);
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
	bCanTrace = false;

	FVector startPos = MotionRight->GetComponentLocation();
	FVector endPos = startPos + MotionRight->GetUpVector() * -100000;

	FHitResult hitInfo;	// �ε��� ���

	bool bHit = HitTest(startPos, endPos, hitInfo);

	// ���� ����Ȱ��� �ִٸ�
	if (bHit)
	{
		if (bCanGrip)
		{
			// �ش� �������� ���

			if (GripProcedural != nullptr)
			{
				GripItem(Cast<AItem>(GripProcedural->GetOwner()));

				params.AddIgnoredComponent(GripProcedural);
				params.AddIgnoredActor(this);
			}
			else if (GripObject != nullptr)
			{
				GripItem(GripObject);

				params.AddIgnoredActor(GripObject);
				params.AddIgnoredActor(this);
			}
			

			// �׸��Ǵ� �� ��ġ���� ������ ���� üũ�ؾ��� ����..
		}


		//if (bHit)
		//{
		//	if (bCanGrip)
		//	{
		//		// ���� ����� �������� 
		//		if (hitInfo.GetActor())
		//		{
		//			MeshRight->SetVisibility(false);
		//			
		//			GripObject->AttachToComponent(MotionRight, FAttachmentTransformRules::KeepWorldTransform);
		//			GripObject->SetActorRelativeLocation(MeshRight->GetComponentLocation(), true);
		//			GripObject->SetActorRelativeRotation(FRotator(0, -90, 90));
		//			
		//			GripObject->SetActorEnableCollision(true);
		//			
		//			// GripObject->baseMesh->SetWorldLocation(MotionRight->GetComponentLocation());
		//			// GripObject->baseMesh->SetSimulatePhysics(false);

		//			params.AddIgnoredActor(GripObject);
		//			params.AddIgnoredActor(this);
		//		}

		//		// ���� ����� �丮��� ProceduralMeshComp
		//		if (hitInfo.GetComponent())
		//		{
		//			MeshRight->SetVisibility(false);

		//			GripProcedural->AttachToComponent(MotionRight, FAttachmentTransformRules::KeepWorldTransform);
		//			GripProcedural->SetRelativeLocation(MeshRight->GetComponentLocation(), true);
		//			GripProcedural->SetRelativeRotation(FRotator(0, -90, 90));

		//			// GripProcedural->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//			GripProcedural->SetSimulatePhysics(false);

		//			GripProcedural->SetWorldLocation(MotionRight->GetComponentLocation());

		//			params.AddIgnoredComponent(GripProcedural);
		//			params.AddIgnoredActor(this);
		//		}

		//	}
		//}

		// �ұ�/���� ���� �� ������ ����Ʈ ��ġ�� ��´�
		//if (GripProcedural != nullptr)	// �� �� �� ��?
		if (GripObject != nullptr)
		{
			FVector grabLoc = GripObject->GetActorLocation();
			FVector dropLoc = grabLoc + FVector(0, 0, -1) * 100000;
			// ������ ����Ʈ �� �۵��ϴ��� Ȯ�ο� �� �׸���
			// DrawLine(grabLoc, dropLoc);
			// ���� �ұ� �ø����� �� �ҽ��� ����ִٸ� 
			if (!GripObject->GetActorNameOrLabel().Contains(TEXT("BP_SliceKnife")))
			{
				// �������� ������ ������ ����Ʈ ǥ��
				CheckHitTraceForLaserPointer(grabLoc, dropLoc);
			}

			bSlice = true;

			//// Į �� ���� ������ ����ִٸ�
			//if (GripObject->GetActorNameOrLabel().Contains(TEXT("BP_SliceKnife")))
			//{
			//	FTimerHandle timerHandle;
			//	// ��Ʈ�ǰ� 0.2�� �ڿ� ���۵ǵ��� ������ �ֱ�
			//	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]() {
			//		// �ڸ� ������ ���� ǥ��
			//		CheckHitTraceForDottedLine(grabLoc, dropLoc);
			//		bSlice = true;
			//		}, 1.f, false);
			//}
		}
	}
}

void ATestCharacter::OnIAUnGripR(const FInputActionValue& value)
{
	bCanTrace = true;
	bSlice = false;

	if (GripObject == nullptr && GripProcedural == nullptr)
		return;

	params.ClearIgnoredActors();
	MeshRight->SetVisibility(true);
	//GripObject->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	if (GripObject != nullptr)
	{
		GripObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GripObject->baseMesh->SetSimulatePhysics(true);
		GripObject->SetActorEnableCollision(true);
	}

	if (GripProcedural != nullptr)
	{
		//GripProcedural->GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//GripProcedural->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		GripProcedural->SetSimulatePhysics(true);
		//GripProcedural->GetOwner()->SetActorEnableCollision(true);
		//GripProcedural->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	if (redDotDecal_inst != nullptr)
	{
		redDotDecal_inst->SetShowDecal(false);
	}
	if (lineDecal_inst != nullptr)
	{
		lineDecal_inst->SetShowDecal(false);
	}

	GripObject = nullptr;
	GripProcedural = nullptr;

}

void ATestCharacter::OnIAGripL(const FInputActionValue& value)
{
}

void ATestCharacter::OnIAUnGripL(const FInputActionValue& value)
{
}

void ATestCharacter::GripItem(AItem* item)
{
	// UE_LOG(LogTemp, Warning, TEXT("hhhhhhhhhhhhhh"));

	if (item != nullptr)
	{
		auto dumbwaiter = Cast<ADumbwaiter>(item);
		if (dumbwaiter != nullptr)
		{
			return;
		}

		// ���� ������Ʈ�� Į �� ���������� ���
		if (item->itemInfoStruct.itemType == ECookingSimulatorItemType::CookingTool)
		{
			// ���� �� �޽ø� ���ְ�
			MeshRight->SetVisibility(false);
			// ���� �������� ��ġ��Ŵ
			item->AttachToComponent(MotionRight, FAttachmentTransformRules::KeepWorldTransform);
			// item->SetActorEnableCollision(ECollisionEnabled::NoCollision);
			item->SetActorEnableCollision(true);
			item->baseMesh->SetSimulatePhysics(false);

			// item->SetActorRelativeLocation(MeshRight->GetComponentLocation() + MeshRight->GetForwardVector() * 700, true);
			item->SetActorRelativeLocation(MeshRight->GetComponentLocation(), true);
			item->SetActorRelativeRotation(FRotator(0, -90, 90));

			MotionRight->GetComponentLocation();
			
			item->baseMesh->SetWorldLocation(MeshRight->GetComponentLocation() + MeshRight->GetRightVector() * 100);
		}		
		else if (item->itemInfoStruct.itemType == ECookingSimulatorItemType::Ingredient) // ���� ������Ʈ�� �丶�� �� �丮����� ���
		{
			if (GripProcedural != nullptr)
			{
				// ���� �� �޽ø� ���ְ�
				MeshRight->SetVisibility(false);
				// ���� �������� ��ġ��Ŵ
				item->AttachToComponent(MotionRight, FAttachmentTransformRules::KeepWorldTransform);
				item->SetActorEnableCollision(ECollisionEnabled::NoCollision);
				//item->SetActorEnableCollision(true);

				item->baseMesh->SetSimulatePhysics(false);
				GripProcedural->SetSimulatePhysics(false);

				// item->SetActorRelativeLocation(MeshRight->GetComponentLocation() + MeshRight->GetForwardVector() * 700, true);
				item->SetActorRelativeLocation(MeshRight->GetComponentLocation(), true);
				item->SetActorRelativeRotation(FRotator(0, -90, 90));

				item->SetActorLocation(MotionRight->GetComponentLocation());
				GripProcedural->SetWorldLocation(MotionRight->GetComponentLocation());
			}
		}

		IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
	}

}


void ATestCharacter::CheckHitTraceForOutline(const FVector& startPos, FVector& endPos)
{
	//if (bCanGrip)
	//	return;

	// lineTrace�� �ؼ� �ε��� ���Ͱ� �ִٸ� ���� �ƿ����� �����ǵ��� �Ӹ�Ƽ�� ���¸� �����Ѵ�
	FHitResult hitInfo;	// �ε��� ���
	bool bHit = HitTest(startPos, endPos, hitInfo);

	AActor* interactedActor = hitInfo.GetActor();
	auto* interactedComp = hitInfo.GetComponent();

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

		auto proceduralMeshCheck = Cast<UProceduralMeshComponent>(interactedComp);

		if (focusedActor != nullptr && interactedActor != focusedActor)
		{
			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
			focusedActor = nullptr;
			targetComp = nullptr;

			// ���⿡�ٰ��� ���°� �³�
			bCanGrip = false;
		}

		if (proceduralMeshCheck != nullptr || item != nullptr)
		{
			focusedActor = interactedActor;

			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, true);

			GripProcedural = Cast<UProceduralMeshComponent>(hitInfo.GetComponent());
			GripObject = Cast<AItem>(hitInfo.GetActor());

			if (GripProcedural != nullptr)
			{
				bCanGrip = true;
			}
			else if (GripObject != nullptr)
			{				
				if (GripObject)
				{
					bCanGrip = true;
				}
			}
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

	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), dropPoint.X, dropPoint.Y, dropPoint.Z);

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

	DrawDebugLine(GetWorld(), start, end, FColor::White, false, 0, 0, 0.5f);
}

bool ATestCharacter::HitTest(FVector start, FVector end, FHitResult& outHit)
{
	/*if (GripObject == nullptr)
	{
		params.AddIgnoredActor(GripObject);
	}*/

	return GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);
}

