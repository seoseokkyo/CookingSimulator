// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingTool.h"
#include "KitchenDial.generated.h"

class UStaticMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API AKitchenDial : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKitchenDial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* bodyMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* dialMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	float limitTime = 3599;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	float currentTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	bool bStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeType")
	bool bSecType = true;

	void SetTimer();

	void ResetTimer();
};
