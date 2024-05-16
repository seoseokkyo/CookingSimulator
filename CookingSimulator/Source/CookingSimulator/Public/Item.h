// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InteractAbleInterface.h"
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
class COOKINGSIMULATOR_API AItem : public AActor, public IInteractAbleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DrawOutLine_Implementation(bool bOn) override;

	virtual void InteractStart_Implementation() override;

	virtual void InteractEnd_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FString ItemName = TEXT("EmptyName");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FCookingSimulatorItemInfo itemInfoStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	UStaticMeshComponent* baseMesh;

private:



	
};
