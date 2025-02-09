// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoItem.h"
#include "FlyGame/Pawns/PlayerPawn.h"
#include "FlyGame/Components/CombatComponent.h"

void AAmmoItem::UpdatePlayerStats(AActor* OtherActor)
{
	if (OtherActor->IsA(PlayerClass))
	{
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

		if (!Player && !Player->GetCombat()) return;

		Player->GetCombat()->UpdateAmmo(GetUpdateValue());

		Destroy();
	}
}