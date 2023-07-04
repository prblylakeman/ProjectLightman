// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PLMAICharacter.h"

// Sets default values
APLMAICharacter::APLMAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APLMAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLMAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

