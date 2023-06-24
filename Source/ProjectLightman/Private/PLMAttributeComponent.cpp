// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMAttributeComponent.h"

// Sets default values for this component's properties
UPLMAttributeComponent::UPLMAttributeComponent()
{
	Health = 100;
}


bool UPLMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	return true;
}



