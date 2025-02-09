// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class FLYGAME_API AHealthItem : public AItem
{
	GENERATED_BODY()

public:
	virtual void UpdatePlayerStats(AActor* OtherActor) override;
};
