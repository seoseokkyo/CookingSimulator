// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

UCLASS()
class COOKINGSIMULATOR_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* VRCamera;	// vr����

	UPROPERTY(EditDefaultsOnly)
	class UMotionControllerComponent* MotionRight;	// ��Ʈ�ѷ�_��
	UPROPERTY(EditDefaultsOnly)
	class UMotionControllerComponent* MotionLeft;	// ��Ʈ�ѷ�_��

	
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* MeshRight;	// ������
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* MeshLeft;		// �޼�

	UPROPERTY(EditDefaultsOnly, Category = VR)
	class UInputAction* IA_MyMove;

	
	UPROPERTY(EditDefaultsOnly, Category = VR)
	class UInputAction* IA_MyTurn;


	UPROPERTY(EditDefaultsOnly, Category = VR)
	class UInputMappingContext* IMC_TestPlayer;

	UPROPERTY()
	class APlayerController* pc;	

	void CheckHitTrace(const FVector& start, const FVector& end);

	void ShowDropPoint(const FVector& start, const FVector& end);

private:
	void DrawLine(FVector start, FVector end);
	bool HitTest(FVector start, FVector end, FHitResult& outHit);
};