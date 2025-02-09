// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;
/**
 * 
 */
UCLASS()
class FLYGAME_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UCameraComponent> PlayerCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UFloatingPawnMovement> PawnMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<class UInputAction> MoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<class UInputAction> LookAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<class UInputAction> FireAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<class UInputAction> AltFireAction = nullptr;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void AltFire();

public:
	//A virtual function that is defined in derived classes: for APlayerPawn, it checks the number of projectiles; for AEnemyPawn, it determines the angle to start shooting.
	virtual void Shoot() override;

	//For using the player's alternative projectiles
	void AltShoot();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
