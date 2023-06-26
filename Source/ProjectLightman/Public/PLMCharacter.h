// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PLMCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UPLMInteractComponent;
class UAnimMontage;
class UPLMAttributeComponent;

UCLASS()
class PROJECTLIGHTMAN_API APLMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Abilities");
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	UAnimMontage* PrimaryAttackAnim;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	UAnimMontage* DashAnim;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	UAnimMontage* BlackHoleAttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_BlackHole;

public:
	// Sets default values for this character's properties
	APLMCharacter();

protected:

	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere);
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere);
	UPLMInteractComponent* InteractComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* MovementAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	UInputAction* UltimateAbilityAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components");
	//UPLMAttributeComponent* AttributeComponent;

	void PrimaryAttackTimeElapsed();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PrimaryAttack();
	void Interact();
	void Dash();
	void Dash_TimeElapsed();
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	virtual void Jump() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
