// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "FlyGame/Pawns/BasePawn.h"
#include "FlyGame/Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "FlyGame/Controllers/BasePlayerController.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;
	AltAmmo = MaxAltAmmo;

	PlayerController = GetOwner()->GetInstigatorController<ABasePlayerController>();

	if (PlayerController)
	{
		PlayerController->SetAmmoHUD(Ammo);
		PlayerController->SetAltAmmoHUD(AltAmmo);
	}

	Pawn = GetOwner<ABasePawn>();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentFireTime += DeltaTime;
}

void UCombatComponent::SpawnEffects(USoundCue* Sound, UParticleSystem* Emitter)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetOwner()->GetActorLocation());
	}

	if (Emitter && Pawn && Pawn->GetMuzzle())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Emitter, Pawn->GetMuzzle()->GetComponentLocation());
	}
}

void UCombatComponent::SpendBulletAmmo()
{
	Ammo = FMath::Clamp(--Ammo, 0, MaxAmmo);
	
	if (PlayerController)
	{
		PlayerController->SetAmmoHUD(Ammo);
	}
}

void UCombatComponent::SpendAltAmmo()
{
	AltAmmo = FMath::Clamp(--AltAmmo, 0, MaxAltAmmo);

	if (PlayerController)
	{
		PlayerController->SetAltAmmoHUD(AltAmmo);
	}
}

bool UCombatComponent::HasAmmo()
{
	return Ammo > 0;
}

bool UCombatComponent::HasAltAmmo()
{
	return AltAmmo > 0;
}

void UCombatComponent::UpdateAmmo(int32 Value)
{
	Ammo = FMath::Clamp(Ammo + Value, 0, MaxAmmo);

	if (PlayerController)
	{
		PlayerController->SetAmmoHUD(Ammo);
	}
}

void UCombatComponent::UpdateAltAmmo(int32 Value)
{
	AltAmmo = FMath::Clamp(AltAmmo + Value, 0, MaxAltAmmo);

	if (PlayerController)
	{
		PlayerController->SetAltAmmoHUD(AltAmmo);
	}
}

void UCombatComponent::Shoot()
{
	if (CurrentFireTime >= FireRate)
	{
		ToSpawnProjectile(DefaultAmmoType);
		SpawnEffects(ShootSound, WeaponMuzzleFlash);
		SpendBulletAmmo();

		CurrentFireTime = 0.f;
	}
}

void UCombatComponent::AltShoot()
{
	ToSpawnProjectile(AltPlayerAmmoType);
	SpawnEffects(AltPlayerShootSound, AltWeaponMuzzleFlash);
	SpendAltAmmo();
}

void UCombatComponent::ToSpawnProjectile(EProjectileType Type)
{
	if (!Pawn) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	Pawn->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = GetOwner();
	SpawnParam.Instigator = GetOwner()->GetInstigator();

	FVector Location = Pawn->GetMuzzle()->GetComponentLocation() + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator Rotation = CameraRotation;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation, SpawnParam);

	if (Projectile)
	{
		Projectile->SetProjectileType(Type);

		FVector LaunchDirection = Rotation.Vector();
		Projectile->FireInDirection(LaunchDirection);
	}
}