// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputActionValue.h>
#include "TestCharacter.generated.h"

class UCameraComponent;
class UMotionControllerComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class AActor;
class APlayerController;

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

private:
	// VR Camera Component를 생성하고 루트에 붙이고 싶다.
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* VRCamera;

	// 모션 컨트롤러 왼손, 오른손을 생성하고 루트에 붙이고 싶다.
	UPROPERTY(EditDefaultsOnly)
	UMotionControllerComponent* MotionLeft;

	UPROPERTY(EditDefaultsOnly)
	UMotionControllerComponent* MotionRight;
	
	// 왼손과 오른손의 스켈레탈 매쉬컴포넌트를 만들고
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshLeft;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshRight;
	
	UPROPERTY(EditAnywhere, Category = "VR")
	UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, Category = "VR")
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "VR")
	UInputAction* IA_Turn;
	
	AActor* focusedActor = nullptr;
	APlayerController* pc = nullptr;

	void OnIAMove(const FInputActionValue& value);
	void OnIATurn(const FInputActionValue& value);

	void DrawLine(FVector startPos, FVector endPos);

	bool HitTest(FVector startPos, FVector endPos, FHitResult& HitResult);

	void CheckHitTrace(const FVector& startPos, FVector& endPos);

	void ShowDropPoint(const FVector& start, const FVector& end);	

public:

};
