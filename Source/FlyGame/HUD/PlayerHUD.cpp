// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include"FlyGame/HUD/PlayerOverlay.h"
#include "Blueprint/UserWidget.h"

void APlayerHUD::AddPlayerOverlay()
{
	APlayerController* PlayerContraler = GetOwningPlayerController();

	if (PlayerContraler && PlayerOverlayClass)
	{
		PlayerOverlay = CreateWidget<UPlayerOverlay>(PlayerContraler, PlayerOverlayClass);

		if (PlayerOverlay)
		{
			PlayerOverlay->AddToViewport();
		}
	}
}
