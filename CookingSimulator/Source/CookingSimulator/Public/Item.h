// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

class UTexture;

USTRUCT(BlueprintType)
struct FCookingSimulatorItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="ItemInfo")
	UTexture* itemImage;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FName itemName;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FText itemDescription;
};

class UStaticMeshComponent;

UCLASS()
class COOKINGSIMULATOR_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	

public:
	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	FCookingSimulatorItemInfo itemInfoStruct;

	UStaticMeshComponent* baseMesh;
};
