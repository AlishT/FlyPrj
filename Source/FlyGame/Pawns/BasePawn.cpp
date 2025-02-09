// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "FlyGame/Components/HealthComponent.h"
#include "FlyGame/Projectiles/Projectile.h"
#include "FlyGame/Components/CombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DefaultRoot"));
	SetRootComponent(CapsuleComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMash"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleOne"));
	Muzzle->SetupAttachment(CapsuleComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComponent->OnHealthChenged.AddDynamic(this, &ABasePawn::EliminationHandler);

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::EliminationHandler(float Health)
{
	if (Health > 0) return;

	if (ElimSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ElimSound, GetActorLocation());
	}

	if (ElimEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElimEffect, GetActorLocation());
	} 

	Destroy();
}

void ABasePawn::Shoot()
{
}





