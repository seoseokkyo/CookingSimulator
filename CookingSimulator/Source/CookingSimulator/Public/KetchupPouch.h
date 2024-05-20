// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingTool.h"
#include "KetchupPouch.generated.h"

class UStaticMesh;
class USplineMeshComponent;
class UMaterialInterface;
class UCableComponent;
class AKetchup;

UCLASS()
class COOKINGSIMULATOR_API AKetchupPouch : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKetchupPouch();

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
	TArray<const USplineMeshComponent*> splineMeshs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TSubclassOf<AKetchup> ketchupActor_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	AKetchup* ketchupActor;

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
