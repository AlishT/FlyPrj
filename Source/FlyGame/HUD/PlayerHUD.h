// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UPlayerOverlay;

/**
 * 
 */
UCLASS()
class FLYGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Player Stats")
	TSubclassOf<class UUserWidget> PlayerOverlayClass;

	UPROPERTY(Transient)
	TObjectPtr<UPlayerOverlay> PlayerOverlay = nullptr;

	void AddPlayerOverlay();
};
