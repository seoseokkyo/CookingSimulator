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
class UInteractComponent;

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

	UPROPERTY(EditAnywhere, Category = "MySettigns")
	class UWidgetComponent* itemWidgetComp;
	
	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class UItemWidget> itemUI_BP;

	UPROPERTY()
	UItemWidget* itemUI = nullptr;

	UPROPERTY(EditAnywhere, Category = "MySettgins")
	class UTexture2D* foodImage;

private:
	// VR Camera Component�� �����ϰ� ��Ʈ�� ���̰� �ʹ�.
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* VRCamera;

	// ��� ��Ʈ�ѷ� �޼�, �������� �����ϰ� ��Ʈ�� ���̰� �ʹ�.
	UPROPERTY(EditDefaultsOnly)
	UMotionControllerComponent* MotionLeft;

	UPROPERTY(EditDefaultsOnly)
	UMotionControllerComponent* MotionRight;
	
	// �޼հ� �������� ���̷�Ż �Ž�������Ʈ�� �����
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshLeft;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshRight;
	
	// �޼հ� �����տ� �� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* GripItemLeft;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* GripItemRight;

	
	UPROPERTY(EditDefaultsOnly, Category = "VR")
	UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	UInputAction* IA_Turn;
	
	UPROPERTY(EditDefaultsOnly, Category = "VR")
	UInputAction* IA_Trigger;

	AActor* focusedActor = nullptr;
	APlayerController* pc = nullptr;

	UInteractComponent* targetComp = nullptr;

	void OnIAMove(const FInputActionValue& value);
	void OnIATurn(const FInputActionValue& value);
	void OnIATrigger(const FInputActionValue& value);

	void DrawLine(FVector startPos, FVector endPos);

	bool HitTest(FVector startPos, FVector endPos, FHitResult& HitResult);

	void CheckHitTraceForOutline(const FVector& startPos, FVector& endPos);

	void CheckHitTraceForLaserPointer(const FVector& startPos, FVector& endPos);

	


public:
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

	UPROPERTY(EditAnywhere, Category = "VR")
	class UPrimitiveComponent* GripObject;


};
