// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UCapsuleComponent;

UCLASS()
class FLYGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UCapsuleComponent> CollisionSphere = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> ItemMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float UpdateValue = 0.f;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<AActor> PlayerClass;

	virtual void UpdatePlayerStats(AActor* OtherActor);

	FORCEINLINE float GetUpdateValue() const { return UpdateValue; }
};
