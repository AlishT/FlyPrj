// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"
#include "FlyGame/Pawns/PlayerPawn.h"
#include "FlyGame/Components/HealthComponent.h"

void AHealthItem::UpdatePlayerStats(AActor* OtherActor)
{
	if (OtherActor->IsA(PlayerClass))
	{
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

		if (!Player && !Player->GetHealthComp())
		{
			return;
		}

		Player->GetHealthComp()->UpdateCurrentHealth(GetUpdateValue());

		Destroy();
	}
}
