// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FlyGame/HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "FlyGame/HUD/PlayerOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ABasePlayerController::BeginPlay()
{
	InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSystem)
	{
		InputSystem->AddMappingContext(InputMapping, 0);
	}

	PlayerHUD = GetHUD<APlayerHUD>();

	if (PlayerHUD)
	{
		PlayerHUD->AddPlayerOverlay();
	}
}

void ABasePlayerController::SetHealthHUD(float MaxHealth, float Health)
{
	bool bValidHUD = PlayerHUD && PlayerHUD->PlayerOverlay && PlayerHUD->PlayerOverlay->HealthBar;

	if (bValidHUD)
	{
		const float HealthPerc = Health / MaxHealth;
		PlayerHUD->PlayerOverlay->HealthBar->SetPercent(HealthPerc);
	}
}

void ABasePlayerController::SetAmmoHUD(int32 Ammo)
{
	bool bValidHUD = PlayerHUD && PlayerHUD->PlayerOverlay && PlayerHUD->PlayerOverlay->AmmoText;

	if (bValidHUD)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		PlayerHUD->PlayerOverlay->AmmoText->SetText(FText::FromString(AmmoText));
	}
}

void ABasePlayerController::SetAltAmmoHUD(int32 AltAmmo)
{
	bool bValidHUD = PlayerHUD && PlayerHUD->PlayerOverlay && PlayerHUD->PlayerOverlay->AltAmmoText;

	if (bValidHUD)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), AltAmmo);
		PlayerHUD->PlayerOverlay->AltAmmoText->SetText(FText::FromString(AmmoText));
	}
}
