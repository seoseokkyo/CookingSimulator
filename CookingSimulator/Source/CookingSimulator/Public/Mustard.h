// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "Mustard.generated.h"

class UStaticMesh;
class USplineMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API AMustard : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMustard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	USplineMeshComponent* splineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	UStaticMesh* splineMesh;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
