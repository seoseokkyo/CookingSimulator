// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <Item.h>


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

	// �÷��� �߿��� �׻� �޼�(���̷�Ż�޽�)���� Ʈ���̽��� ����ȴ�
	FVector start = MeshLeft->GetComponentLocation();
	FVector end = start + MeshLeft->GetRightVector() * 100000;

	// �� �����ϴ��� Ȯ�ο� �� �׸���
	DrawLine(start,end);

	// �ε�ģ ����� ��ȣ�ۿ� ������ ���Ͷ�� �ܰ��� �������� �Ѵ�
	// RenderCustomDepth ���
	CheckHitTrace(start, end);
	
	FVector grabLoc = MeshRight->GetComponentLocation();
	FVector dropLoc = grabLoc + MotionRight->GetUpVector() * -1000;


}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestCharacter::CheckHitTrace(const FVector& start, const FVector& end)
{
	// lineTrace�� �ؼ� �ε��� ���Ͱ� �ִٸ� ���� �ƿ����� �����ǵ��� �Ӹ�Ƽ�� ���¸� �����Ѵ�
	FHitResult hitInfo;	// �ε��� ���
	bool bHit = HitTest(start, end, hitInfo);

	AActor* interactedActor = hitInfo.GetActor();

	if (bHit)
	{
		// �ε��� ������ Render CustomDepthPass�� true�� �����Ѵ�
		// Cast<AItem>(interactedActor)->baseMesh->SetCustomDepthStencilValue();
		auto item = Cast<AItem>(interactedActor);
		if (item != nullptr)
		{
			item->baseMesh->SetRenderCustomDepth(true);
		}
		
	}
	else
	{
		auto item = Cast<AItem>(interactedActor);
		if (item != nullptr)
		{
			// �ε��� ������ Render CustomDepthPass�� false�� �����Ѵ�
			item->baseMesh->SetRenderCustomDepth(false);
		}	
	}
}

void ATestCharacter::ShowDropPoint(const FVector& start, const FVector& end)
{
	FHitResult hitInfo;
	bool bHit = HitTest(start, end, hitInfo);

	FVector dropPoint = hitInfo.ImpactPoint;

	if (bHit)
	{
		
	}
	else 
	{

	}
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

