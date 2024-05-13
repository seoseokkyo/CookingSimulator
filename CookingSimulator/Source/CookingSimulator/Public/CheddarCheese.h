// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.h"
#include "CheddarCheese.generated.h"

UCLASS()
class COOKINGSIMULATOR_API ACheddarCheese : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheddarCheese();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};