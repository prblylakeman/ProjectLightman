// Fill out your copyright notice in the Description page of Project Settings.


#include "PLMCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PLMInteractComponent.h"
#include "PLMAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APLMCharacter::APLMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractComponent = CreateDefaultSubobject<UPLMInteractComponent>("InteractComponent");

	AttributeComponent = CreateDefaultSubobject<UPLMAttributeComponent>("AttributeComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	SocketName = "WeaponSocket";

	TimeToHitParameter = "TimeToHit";
}

void APLMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnChangeInitiated.AddDynamic(this, &APLMCharacter::OnChangeInitiated);
}

// Called when the game starts or when spawned
void APLMCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}

void APLMCharacter::MoveForward(const FInputActionValue& Value)
{
	if (bCanMove == true)
	{
		const float DirectionValue = Value.Get<float>();

		if (Controller && (DirectionValue != 0.f))
		{
			FRotator ControlRot = GetControlRotation();
			ControlRot.Pitch = 0.f;
			ControlRot.Roll = 0.f;
			AddMovementInput(ControlRot.Vector(), DirectionValue);
		}
	}
}

void APLMCharacter::MoveRight(const FInputActionValue& Value)
{
	if (bCanMove == true)
	{
		const float RightValue = Value.Get<float>();

		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.f;
		ControlRot.Roll = 0.f;

		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		AddMovementInput(RightVector, RightValue);
	}
}

void APLMCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void APLMCharacter::PrimaryAttack()
{
	if (bCanMove == true)
	{
		PlayAnimMontage(PrimaryAttackAnim);
		UGameplayStatics::SpawnEmitterAttached(PrimaryCastEffect, GetMesh(), SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &APLMCharacter::PrimaryAttackTimeElapsed, PrimaryAttackDelay);
	}


	// clear timer code GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void APLMCharacter::PrimaryAttackTimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}


void APLMCharacter::Interact()
{
	if (InteractComponent)
	{
		if (bCanMove == true)
		{
			InteractComponent->PrimaryInteract();
		}
	}
}

void APLMCharacter::Dash()
{
	if (bCanMove == true)
	{
		PlayAnimMontage(DashAnim);
		UGameplayStatics::SpawnEmitterAttached(DashCastEffect, GetMesh(), SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &APLMCharacter::Dash_TimeElapsed, DashAnimDelay);
	}
}

void APLMCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void APLMCharacter::BlackHoleAttack()
{
	if (bCanMove == true)
	{
		PlayAnimMontage(BlackHoleAttackAnim);
		UGameplayStatics::SpawnEmitterAttached(BlackHoleCastEffect, GetMesh(), SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		GetWorldTimerManager().SetTimer(TimerHandle_BlackHole, this, &APLMCharacter::BlackHoleAttack_TimeElapsed, BlackHoleAnimDelay);
		
		bCanMove = false;
	}
	//Controller->SetIgnoreMoveInput(true);
}

void APLMCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);

	bCanMove = true;
}

void APLMCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		
		FVector HandLocation = GetMesh()->GetSocketLocation(SocketName);

		if (ClassToSpawn == BlackHoleProjectileClass)
		{
			HandLocation.Z += BlackHoleOffset;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComponent->GetComponentLocation();

		FVector TraceEnd = CameraComponent->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}


void APLMCharacter::Jump()
{
	if (bCanMove == true)
	{
		Super::Jump();
	}
}

void APLMCharacter::OnChangeInitiated(AActor* InstigatorActor, UPLMAttributeComponent* OwningComponent, int NewHealth, int Delta)
{
	if (Delta < 0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParameter, GetWorld()->TimeSeconds);
	}
	
	if (NewHealth <= 0 && Delta < 0)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}

// Called every frame
void APLMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APLMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APLMCharacter::Jump);

		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APLMCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APLMCharacter::MoveRight);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APLMCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APLMCharacter::Interact);

		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &APLMCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(MovementAbilityAction, ETriggerEvent::Triggered, this, &APLMCharacter::Dash);
		EnhancedInputComponent->BindAction(UltimateAbilityAction, ETriggerEvent::Triggered, this, &APLMCharacter::BlackHoleAttack);
	}
}

