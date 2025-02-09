// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "FlyGame/Components/CombatComponent.h"

AEnemyPawn::AEnemyPawn()
{
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(GetBaseMesh());

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(TurretMesh);

	GetMuzzle()->SetupAttachment(WeaponMesh);
}

void AEnemyPawn::Shoot()
{
	FVector CurrentDirection = TurretMesh->GetForwardVector();
	FVector TargetDirection = TargetLocation - TurretMesh->GetComponentLocation();

	float RotationAngleCosine = CurrentDirection.CosineAngle2D(TargetDirection);
	float RotationAngle = FMath::RadiansToDegrees(FMath::Acos(RotationAngleCosine));

	if (RotationAngle <= TurretAimError && GetCombat())
	{
		GetCombat()->Shoot();
	}
}

void AEnemyPawn::RotateTurret()
{
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator StartRotation = TurretMesh->GetComponentRotation();

	FVector TurretDirection = TargetLocation - StartLocation;
	TurretDirection.Z = 0.f;

	FRotator Rotation = TurretDirection.Rotation();
	Rotation.Normalize();

	FRotator TurretRotation = FMath::RInterpConstantTo(StartRotation, Rotation, RotateTime, TurretRotateSpeed);

	TurretMesh->SetWorldRotation(TurretRotation);
}

void AEnemyPawn::RotateWeapon()
{
	FVector StartLocation = WeaponMesh->GetComponentLocation();
	FRotator StartRotation = WeaponMesh->GetComponentRotation();

	FVector WeaponDirection = TargetLocation - StartLocation;

	FRotator Rotation = WeaponDirection.Rotation();
	Rotation.Normalize();

	FRotator WeaponRotation = FMath::RInterpConstantTo(StartRotation, Rotation, RotateTime, WeaponRotateSpeed);

	WeaponRotation.Pitch = FMath::Clamp(WeaponRotation.Pitch, MinAngle, MaxAngle);

	WeaponMesh->SetWorldRotation(WeaponRotation);
}
