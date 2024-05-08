// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.h"
#include "Potato.generated.h"

UCLASS()
class COOKINGSIMULATOR_API APotato : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotato();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
