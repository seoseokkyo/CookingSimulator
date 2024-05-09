// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingTool.h"
#include "Dumbwaiter.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class COOKINGSIMULATOR_API ADumbwaiter : public ACookingTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADumbwaiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UStaticMeshComponent* leftDoor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	UBoxComponent* boxComp;

};
