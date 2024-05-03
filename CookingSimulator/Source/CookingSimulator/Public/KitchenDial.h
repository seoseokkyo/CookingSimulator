// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KitchenDial.generated.h"

class UStaticMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API AKitchenDial : public AActor
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

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	float limitTime = 3599;

	float currentTime = 0.f;

	bool bStart = false;

	void SetTimer();
};
