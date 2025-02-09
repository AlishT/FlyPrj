// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FlyGame/Components/CombatComponent.h"

APlayerPawn::APlayerPawn()
{
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetRootComponent());
	PlayerCamera->bUsePawnControlRotation = true;

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* PlayerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerEnhancedInput)
	{
		PlayerEnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		PlayerEnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::Look);
		PlayerEnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerPawn::Fire);
		PlayerEnhancedInput->BindAction(AltFireAction, ETriggerEvent::Triggered, this, &APlayerPawn::AltFire);
	}
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector DirectionVector = Value.Get<FVector>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		AddMovementInput(ForwardDirection, DirectionVector.Y);
		AddMovementInput(RightDirection, DirectionVector.X);
		AddMovementInput(UpDirection, DirectionVector.Z);
	}
}

void APlayerPawn::Look(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	AddControllerYawInput(Direction.X);
	AddControllerPitchInput(Direction.Y);
}

void APlayerPawn::Fire()
{
	Shoot();
}

void APlayerPawn::AltFire()
{
	AltShoot();
}

void APlayerPawn::Shoot()
{
	bool bCanFire = GetCombat() && GetCombat()->HasAmmo();

	if (bCanFire)
	{
		GetCombat()->Shoot();
	}
}

void APlayerPawn::AltShoot()
{
	bool bCanFire = GetCombat() && GetCombat()->HasAltAmmo();

	if (bCanFire)
	{
		GetCombat()->AltShoot();
	}
}

