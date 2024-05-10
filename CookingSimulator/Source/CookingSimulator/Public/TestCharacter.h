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


public:
	// VR Camera Component�� �����ϰ� ��Ʈ�� ���̰� �ʹ�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	// ��� ��Ʈ�ѷ� �޼�, �������� �����ϰ� ��Ʈ�� ���̰� �ʹ�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMotionControllerComponent* MotionLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMotionControllerComponent* MotionRight;
	
	// �޼հ� �������� ���̷�Ż �Ž�������Ʈ�� �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* MeshLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MeshRight;

	
	// �޼հ� �����տ� �� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* GripItemLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* GripItemRight;

	
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

	void CheckHitTraceForOutline(const FVector& startPos, FVector& endPos);

	void CheckHitTraceForLaserPointer(const FVector& startPos, FVector& endPos);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APointDecalActor> PointDecalActor;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALineDecalActor> LineDecalActor;
	

	bool bshowDecal = false;

	class APointDecalActor* redDotDecal_inst = nullptr;
	class ALineDecalActor* lineDecal_inst = nullptr;

	UPROPERTY(EditAnywhere, Category = "VR")
	UInputAction* IA_MyGripR;
	void OnIAGripR(const FInputActionValue& value);
	void OnIAUnGripR(const FInputActionValue& value);
		
	UPROPERTY(EditAnywhere, Category = "VR")
	UInputAction* IA_MyGripL; 
	void OnIAGripL(const FInputActionValue& value);
	void OnIAUnGripL(const FInputActionValue& value);

	void GripItem(UPrimitiveComponent* item);

	bool bCanGrip = false;

	bool bGripSauce = true;
	bool bGripCookingTool = true;

	void CheckHitTraceForDottedLine(const FVector& startPos, FVector& endPos);

	UPROPERTY()
	class UPrimitiveComponent* GripObject;
};
