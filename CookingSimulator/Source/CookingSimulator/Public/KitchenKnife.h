// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingTool.h"
#include "KitchenKnife.generated.h"

UCLASS()
class COOKINGSIMULATOR_API AKitchenKnife : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKitchenKnife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	UStaticMeshComponent* knifeMesh;

};
