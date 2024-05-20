// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tablet.generated.h"

UCLASS()
class COOKINGSIMULATOR_API ATablet : public AActor
{
	GENERATED_BODY()
	
public:	
	ATablet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UWidgetComponent* menuWidgetComp;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UStaticMeshComponent* tabletMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category="VR")
	TSubclassOf<class UMenuWidget> menuUI_BP;
	
	UPROPERTY()
	UMenuWidget* menuUI;
};
