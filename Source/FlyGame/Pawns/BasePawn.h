// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyGame/ProjectileType.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UHealthComponent;
class UCombatComponent;
class USoundCue;
class UParticleSystem;

UCLASS()
class FLYGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UCapsuleComponent> CapsuleComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> BaseMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<USceneComponent> Muzzle = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UHealthComponent> HealthComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UCombatComponent> CombatComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<USoundCue> ElimSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UParticleSystem> ElimEffect = nullptr;

	UFUNCTION()
	void EliminationHandler(float Health);

public:
	virtual void Shoot();

	FORCEINLINE UStaticMeshComponent* GetBaseMesh() const{ return BaseMesh; }
	FORCEINLINE UHealthComponent* GetHealthComp() const { return HealthComponent; }
	FORCEINLINE USceneComponent* GetMuzzle() const { return Muzzle; }
	FORCEINLINE UCombatComponent* GetCombat() const { return CombatComp; }
};
