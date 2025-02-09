// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class APlayerHUD;

/**
 * 
 */
UCLASS()
class FLYGAME_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	TObjectPtr<class UInputMappingContext> InputMapping = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerHUD> PlayerHUD = nullptr;

public:
	void SetHealthHUD(float MaxHealth, float Health);

	void SetAmmoHUD(int32 Ammo);
	void SetAltAmmoHUD(int32 AltAmmo);
};
