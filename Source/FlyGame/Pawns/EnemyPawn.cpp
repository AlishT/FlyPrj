// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

AEnemyPawn::AEnemyPawn()
{
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(GetBaseMesh());

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(TurretMesh);

	GetMuzzle()->SetupAttachment(WeaponMesh);
}

void AEnemyPawn::RotateTurret(FVector& TargetLocation)
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

void AEnemyPawn::RotateWeapon(FVector& TargetLocation)
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
