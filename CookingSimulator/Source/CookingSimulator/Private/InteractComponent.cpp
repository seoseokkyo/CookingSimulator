// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

void UInteractComponent::DrawOutLine_Implementation(bool bOn)
{
	SetRenderCustomDepth(bOn);

	SetCustomDepthStencilValue(bOn ? 1 : 0);
}

void UInteractComponent::InteractStart_Implementation()
{
	if (startEventDelegate.IsBound())
	{
		startEventDelegate.Execute();
	}

	bState ^= true;
}

void UInteractComponent::InteractEnd_Implementation()
{
	if (endEventDelegate.IsBound())
	{
		endEventDelegate.Execute();
	}
}

