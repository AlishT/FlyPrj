// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class FLYGAME_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> TurretMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float RotateTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float TurretRotateSpeed = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float WeaponRotateSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float MaxAngle = 45.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float MinAngle = -20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default", meta = (Units = "Degrees"))
	float TurretAimError = 0.f;

	UPROPERTY()
	FVector TargetLocation = FVector::ZeroVector;


public:
	virtual void Shoot() override;

	void RotateTurret();
	
	void RotateWeapon();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	FORCEINLINE void SetTargetLocation(const FVector& Location) { TargetLocation = Location; }
};
