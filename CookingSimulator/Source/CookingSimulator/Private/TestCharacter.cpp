


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
#include "Ketchup.h"
#include "KetchupPouch.h"
#include "ProceduralMeshComponent.h"
#include "ItemWidget.h"
#include "Components/CanvasPanel.h"
#include "CookingSimulatorFunctionLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Tablet.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMeshSocket.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h>


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

	// 오른손에 쥘 스테틱메시컴포넌트
	GripItemRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripRightItem"));
	GripItemRight->SetupAttachment(MotionRight);
	GripItemRight->SetVisibility(false);

	// 왼손에 쥘 스테틱메시컴포넌트
	GripItemLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripLeftItem"));
	GripItemLeft->SetupAttachment(MotionLeft);
	GripItemLeft->SetVisibility(false);

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

	// 아이템 위젯 컴포넌트를 생성한다
	itemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item Widget Component"));
	itemWidgetComp->SetupAttachment(RootComponent);
	itemWidgetComp->SetWorldRotation(FRotator(180, 0, 0));
	itemWidgetComp->SetWorldScale3D(FVector(0.3f));
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 아이템 UI가 있다면 생성하고 숨긴다.
	if (itemWidgetComp != nullptr)
	{
		itemUI = Cast<UItemWidget>(itemWidgetComp->GetWidget());
		itemUI->SetVisibility(ESlateVisibility::Hidden);
	}

	// 태블릿을 왼손에 attach하고 숨긴다
	if (tablet_BP != nullptr)
	{
		spawnTablet = GetWorld()->SpawnActor<ATablet>(tablet_BP);

		const USkeletalMeshSocket* tabletSocket = MeshLeft->GetSocketByName("TabletSocket");


		if (spawnTablet && tabletSocket)
		{
			tabletSocket->AttachActor(spawnTablet, MeshLeft);
			//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("rr")));
			spawnTablet->AttachToComponent(MeshLeft, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("TabletSocket")));
		}
		else
		{
			//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("null")));
		}

		spawnTablet->SetActorHiddenInGame(true);
	}


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


	// 레이저 포인트 데칼

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


	// 플레이 중에는 항상 왼손(스켈레탈메시)에서 트레이싱이 진행된다
	FVector start = MeshRight->GetComponentLocation();
	FVector end = start + MeshRight->GetRightVector() * 100000;

	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("bCanTrace State : %s(%d)"), bCanTrace ? L"TRUE" : L"FALSE", DeltaTime));

	// 부딪친 대상이 상호작용 가능한 액터라면 외각선 렌더링을 한다
	// RenderCustomDepth 사용
	if (bCanTrace)
	{
		// 아웃라인 잘 동작하는지 확인용 선 그리기
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

		input->BindAction(IA_RightButtonB, ETriggerEvent::Started, this, &ATestCharacter::OnIARightButtonPressB);
		input->BindAction(IA_RightButtonB, ETriggerEvent::Completed, this, &ATestCharacter::OnIARightButtonReleaseB);

		input->BindAction(IA_ShowTablet, ETriggerEvent::Started, this, &ATestCharacter::ShowTablet);

		input->BindAction(IA_Plating, ETriggerEvent::Started, this, &ATestCharacter::OnIAPlating);
	}

	// 나중에 문제 해결되면 삭제 예정
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


// 태블릿 띄우고 숨기는 함수
void ATestCharacter::ShowTablet(const FInputActionValue& value)
{
	// bshow 가 false라면 태블릿을 띄우고 bshow를 true로 바꾼다
	if (false == bshow)
	{
		spawnTablet->SetActorHiddenInGame(false);
		bshow = true;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("sr")));
	}
	// bshow 가 true라면 태블릿을 숨기고 false로 바꾼다
	else
	{
		spawnTablet->SetActorHiddenInGame(true);
		bshow = false;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("none")));
	}
}

void ATestCharacter::OnIARightButtonPressB(const FInputActionValue& value)
{
	auto ketchupCheck = Cast<AKetchupPouch>(GripObject);
	if (ketchupCheck != nullptr)
	{
		ketchupCheck->DrawStart();
	}
}

void ATestCharacter::OnIARightButtonReleaseB(const FInputActionValue& value)
{
	auto ketchupCheck = Cast<AKetchupPouch>(GripObject);
	if (ketchupCheck != nullptr)
	{
		ketchupCheck->DrawStop();
	}
}

void ATestCharacter::OnIAPlating(const FInputActionValue& value)
{
	if (GripProcedural != nullptr)
	{
		FVector start = GripProcedural->GetComponentLocation();
		FVector end = start + GetActorUpVector() * -500;

		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0, 0, 0.5f);

		FHitResult hitInfo;
		bool bHit = HitTest(start, end, hitInfo);

		bool bHandIsOnPlate = false;

		if (bHit)
		{
			if (hitInfo.GetActor()->GetActorNameOrLabel().Contains(TEXT("plate")))
			{
				bHandIsOnPlate = true;
				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("plate")));


				// 손에 식재료를 잡고 있을 때 && 그릇이라는 아이템에 포커스가 들어가 있을 때
				if (bHoldingIngredientNow && bHandIsOnPlate)
				{
					GripProcedural->GetOwner()->AttachToActor(hitInfo.GetActor(), FAttachmentTransformRules::SnapToTargetIncludingScale);
					UnGripNow();
				}

			}
		}
	}

}

void ATestCharacter::OnIAGripR(const FInputActionValue& value)
{
	bCanTrace = false;

	FVector startPos = MotionRight->GetComponentLocation();
	FVector endPos = startPos + MotionRight->GetUpVector() * -100000;

	FHitResult hitInfo;	// 부딪힌 대상

	bool bHit = HitTest(startPos, endPos, hitInfo);

	if (bCanGrip)
	{
		// 해당 아이템을 쥔다

		if (GripProcedural != nullptr)
		{
			GripItem(Cast<AItem>(GripProcedural->GetOwner()));

			params.AddIgnoredComponent(GripProcedural);
			params.AddIgnoredActor(this);

			bHoldingIngredientNow = true;
		}
		else if (GripObject != nullptr)
		{
			GripItem(GripObject);

			params.AddIgnoredActor(GripObject);
			params.AddIgnoredActor(this);
		}


		// 그립되는 이 위치에서 무시할 액터 체크해야함 주의..
	}

	// 만약 검출된것이 있다면
	if (bHit)
	{



		//if (bHit)
		//{
		//	if (bCanGrip)
		//	{
		//		// 닿은 대상이 조리도구 
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

		//		// 닿은 대상이 요리재료 ProceduralMeshComp
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

		// 소금/후추 등이 들어갈 레이저 포인트 위치를 잡는다
		//if (GripProcedural != nullptr)	// 왜 둘 다 돼?
		if (GripObject != nullptr)
		{
			FVector grabLoc = GripObject->GetActorLocation();
			FVector dropLoc = grabLoc + FVector(0, 0, -1) * 100000;
			// 레이저 포인트 잘 작동하는지 확인용 선 그리기
			// DrawLine(grabLoc, dropLoc);
			// 케찹 소금 올리브유 등 소스를 잡고있다면 
			if (!GripObject->GetActorNameOrLabel().Contains(TEXT("BP_SliceKnife")))
			{
				// 떨어지는 지점에 레이저 포인트 표시
				CheckHitTraceForLaserPointer(grabLoc, dropLoc);
			}

			bSlice = true;

			//// 칼 등 조리 도구를 잡고있다면
			//if (GripObject->GetActorNameOrLabel().Contains(TEXT("BP_SliceKnife")))
			//{
			//	FTimerHandle timerHandle;
			//	// 히트되고 0.2초 뒤에 동작되도록 딜레이 넣기
			//	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]() {
			//		// 자를 지점에 점선 표시
			//		CheckHitTraceForDottedLine(grabLoc, dropLoc);
			//		bSlice = true;
			//		}, 1.f, false);
			//}
		}
	}
}

void ATestCharacter::OnIAUnGripR(const FInputActionValue& value)
{
	UnGripNow();

	//bCanTrace = true;
	//bSlice = false;

	//if (GripObject == nullptr && GripProcedural == nullptr)
	//	return;

	//params.ClearIgnoredActors();
	//MeshRight->SetVisibility(true);
	////GripObject->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	//if (GripObject != nullptr)
	//{
	//	GripObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//	GripObject->baseMesh->SetSimulatePhysics(true);
	//	GripObject->SetActorEnableCollision(true);
	//}

	//if (GripProcedural != nullptr)
	//{
	//	//GripProcedural->GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//	//GripProcedural->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//	GripProcedural->SetSimulatePhysics(true);
	//	//GripProcedural->GetOwner()->SetActorEnableCollision(true);
	//	//GripProcedural->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//}

	//if (redDotDecal_inst != nullptr)
	//{
	//	redDotDecal_inst->SetShowDecal(false);
	//}
	//if (lineDecal_inst != nullptr)
	//{
	//	lineDecal_inst->SetShowDecal(false);
	//}

	//auto ketchupCheck = Cast<AKetchupPouch>(GripObject);

	//if (ketchupCheck != nullptr)
	//{
	//	ketchupCheck->DrawStop();
	//	ketchupCheck->ReleaseTargetPoint();
	//}

	//GripObject = nullptr;
	//GripProcedural = nullptr;

	//bHoldingIngredientNow = false;

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

		// 잡은 오브젝트가 칼 등 조리도구인 경우
		if (item->itemInfoStruct.itemType == ECookingSimulatorItemType::CookingTool)
		{
			// 기존 손 메시를 없애고
			MeshRight->SetVisibility(false);
			// 잡은 아이템을 위치시킴
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
		else if (item->itemInfoStruct.itemType == ECookingSimulatorItemType::Ingredient) // 잡은 오브젝트가 토마토 등 요리재료인 경우
		{
			if (GripProcedural != nullptr)
			{
				// 기존 손 메시를 없애고
				MeshRight->SetVisibility(false);
				// 잡은 아이템을 위치시킴
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

	// lineTrace를 해서 부딪힌 액터가 있다면 액터 아웃라인 강조되도록 머리티얼 상태를 변경한다
	FHitResult hitInfo;	// 부딪힌 대상
	bool bHit = HitTest(startPos, endPos, hitInfo);

	AActor* interactedActor = hitInfo.GetActor();
	auto* interactedComp = hitInfo.GetComponent();

	UInteractComponent* compCheck = Cast<UInteractComponent>(hitInfo.GetComponent());

	params.AddIgnoredComponent(itemWidgetComp);

	if (compCheck != nullptr)
	{
		targetComp = compCheck;
	}

	if (bHit)
	{

		FString strTemp;
		hitInfo.GetActor()->GetName(strTemp);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s"), *strTemp));

		hitInfo.GetComponent()->GetName(strTemp);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s"), *strTemp));


		// 부딪힌 액터의 Render CustomDepthPass를 true로 변경한다
		// Cast<AItem>(interactedActor)->baseMesh->SetCustomDepthStencilValue();
		auto item = Cast<AItem>(interactedActor);

		auto proceduralMeshCheck = Cast<UProceduralMeshComponent>(interactedComp);

		if (focusedActor != nullptr && interactedActor != focusedActor)
		{
			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, false);
			focusedActor = nullptr;
			targetComp = nullptr;

			// 여기에다가도 쓰는게 맞나
			bCanGrip = false;

			hitPoint = FVector::ZeroVector;

			itemUI->SetVisibility(ESlateVisibility::Hidden);
		}

		if (proceduralMeshCheck != nullptr || item != nullptr)
		{
			focusedActor = interactedActor;

			hitPoint = hitInfo.ImpactPoint;

			IInteractAbleInterface::Execute_DrawOutLine(focusedActor, true);
			//IInteractAbleInterface::Execute_DrawOutLine(proceduralMeshCheck->GetOwner(), true);

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


			// 이미지 가져오는 부분 확실하지 않아서 점검 필요
			ACookingSimulatorGameModeBase* gm = GetWorld()->GetAuthGameMode<ACookingSimulatorGameModeBase>();

			// itemWidget을 빌보드 처리한다
			auto* fpc = GetWorld()->GetFirstPlayerController();
			if (fpc != nullptr)
			{
				FVector dir = fpc->PlayerCameraManager->GetCameraLocation() - itemWidgetComp->GetComponentLocation();
				itemWidgetComp->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(dir.GetSafeNormal()));

				//itemWidgetComp->SetWorldLocation(fpc->PlayerCameraManager->GetCameraLocation() + fpc->PlayerCameraManager->GetActorForwardVector() * 500);
				itemWidgetComp->SetWorldLocation(focusedActor->GetActorLocation() + focusedActor->GetActorUpVector() * 100);
			}

			if (item != nullptr)
			{
				//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("rr")));
				FString itemName_ = item->ItemName;
				if (itemName_.Compare(TEXT("Name")) != 0)
					itemUI->SetVisibility(ESlateVisibility::Visible);
				{
					FText itemNameText = FText::FromString(itemName_);
					itemUI->itemName->SetText(itemNameText);
					foodImage = UCookingSimulatorFunctionLibrary::GetImageByItemName(GetWorld(), itemName_);
					itemUI->itemImage->SetBrushFromSoftTexture(foodImage);
					UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("rr")));
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

			hitPoint = FVector::ZeroVector;
		}


		// 다시 아이템 UI 숨기기
		itemUI->SetVisibility(ESlateVisibility::Hidden);
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

		endPos = hitInfo.ImpactPoint;
	}
	else
	{
		if (lineDecal_inst != nullptr)
		{
			lineDecal_inst->SetShowDecal(false);
		}
	}
}

void ATestCharacter::UnGripNow()
{
	bCanTrace = true;
	bSlice = false;
	bCanGrip = false;

	params.ClearIgnoredActors();

	if (GripObject == nullptr && GripProcedural == nullptr)
		return;


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

	auto ketchupCheck = Cast<AKetchupPouch>(GripObject);

	if (ketchupCheck != nullptr)
	{
		ketchupCheck->DrawStop();
		ketchupCheck->ReleaseTargetPoint();
	}

	GripObject = nullptr;
	GripProcedural = nullptr;

	bHoldingIngredientNow = false;
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

