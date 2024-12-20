// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingTool.h"
#include "SaltBottle.generated.h"

class UStaticMesh;
class USplineMeshComponent;
class UMaterialInterface;
class ASalt;

UCLASS()
class COOKINGSIMULATOR_API ASaltBottle : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaltBottle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bStart;

	FVector targetPoint;

	bool bTargetOn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	//UCableComponent* cableComp;

	TArray<FVector> splinePositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TSubclassOf<ASalt> saltActor_BP;

	UPROPERTY(VisibleAnywhere, Category="MySettings|Components")
	class UAudioComponent* soundComp_Salt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	ASalt* saltActor;

	float delayTime = 0.0f;

	void DrawStart() { bStart = true; };
	void DrawStop() { bStart = false; };

	UFUNCTION()
	void OnAddNewPosition(FVector newPos, FHitResult& hitResult);

	UFUNCTION()
	void SetTargetPoint(FVector _targetPoint);

	UFUNCTION()
	void ReleaseTargetPoint();

	void RotationToTarget();
};
