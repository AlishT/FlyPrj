// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "FlyGame/Controllers/BasePlayerController.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
		PlayerController = GetOwner()->GetInstigatorController<ABasePlayerController>();

		if (PlayerController)
		{
			PlayerController->SetHealthHUD(MaxHealth, CurrentHealth);
		}
	}
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0,  MaxHealth);

	if (PlayerController)
	{
		PlayerController->SetHealthHUD(MaxHealth, CurrentHealth);
	}

	OnHealthChenged.Broadcast(CurrentHealth);
}

void UHealthComponent::UpdateCurrentHealth(float Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Health, 0, MaxHealth);

	if (PlayerController)
	{
		PlayerController->SetHealthHUD(MaxHealth, CurrentHealth);
	}
}
