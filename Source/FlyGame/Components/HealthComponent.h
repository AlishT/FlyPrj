// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ABasePlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChenged, float, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLYGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<ABasePlayerController> PlayerController = nullptr;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser);

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChenged OnHealthChenged;

	//Restores CurrentHealth, updates the health bar, and is called in AHealthItem
	void UpdateCurrentHealth(float Health);

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetMaxHealth(const float Health) { MaxHealth = Health; }
};
