// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"


UENUM(BlueprintType)
enum class ECookingSimulatorItemType : uint8
{
	Ingredient,
	CookingTool
};

USTRUCT(BlueprintType)
struct FCookingSimulatorItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	ECookingSimulatorItemType itemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FString itemImagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FString itemDescription;
};


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FCookingSimulatorItemInfo itemInfoStruct;

};
