// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyGame/ProjectileType.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AProjectile;
class USoundCue;
class ABasePlayerController;
class UParticleSystem;
class ABasePawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLYGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	EProjectileType DefaultAmmoType = EProjectileType::EPT_Bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	EProjectileType AltPlayerAmmoType = EProjectileType::EPT_Bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	TObjectPtr<USoundCue> ShootSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	TObjectPtr<USoundCue> AltPlayerShootSound = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> WeaponMuzzleFlash = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> AltWeaponMuzzleFlash = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	FVector MuzzleOffset = FVector::ZeroVector;

	UPROPERTY(Transient)
	TObjectPtr<ABasePawn> Pawn = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	float FireRate = 0.f;

	UPROPERTY()
	float CurrentFireTime = 0.f;

	UPROPERTY()
	int32 Ammo = 0;
	
	UPROPERTY()
	int32 AltAmmo = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	int32 MaxAmmo = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	int32 MaxAltAmmo = 0;

	UPROPERTY(Transient)
	TObjectPtr<ABasePlayerController> PlayerController = nullptr;

	void SpawnEffects(USoundCue* Sound, UParticleSystem* Emitter);

	void SpendBulletAmmo();

	void SpendAltAmmo();

public:
	void Shoot();
	
	void AltShoot();

	bool HasAmmo();

	bool HasAltAmmo();

	void UpdateAmmo(int32 Value);

	void UpdateAltAmmo(int32 Value);
	
	void ToSpawnProjectile(EProjectileType Type);
};
