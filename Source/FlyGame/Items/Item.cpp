// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/CapsuleComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);

	CollisionSphere->SetCapsuleRadius(500);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UpdatePlayerStats(OtherActor);
}

void AItem::UpdatePlayerStats(AActor* OtherActor)
{
}

