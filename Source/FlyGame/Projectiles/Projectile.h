#pragma once

#include "CoreMinimal.h"
#include "FlyGame/ProjectileType.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;
class UParticleSystem;

USTRUCT(BlueprintType)
struct FLYGAME_API FProjectileData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Name = "NONE";

	UPROPERTY(EditDefaultsOnly)
	float Damage = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> ProjectileMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> TrailSystem = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> ImpactSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> AirLoopSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactPartical = nullptr;
};

UCLASS()
class FLYGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionBox")
	TObjectPtr<UBoxComponent> CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileMovementComponent")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> TrailSystem = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraComponent>TrailSystemComponent = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<USoundCue>ImpactSound = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<USoundCue>AirLoopSound = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UAudioComponent> AirLoopComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<USoundAttenuation> LoopingSoundAttenuation = nullptr;

	UPROPERTY(Transient)
	TObjectPtr <UParticleSystem> ImpactPartical = nullptr;

	UPROPERTY()
	float Damage = 0.f;

	UPROPERTY()
	float DestroyTime = 2.f;

	UPROPERTY()
	float CurrentTime = 0.f;

	UPROPERTY()
	bool bHit = false;;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	TObjectPtr<class UDataTable> ProjectileDataTable = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	EProjectileType ProjectileType = EProjectileType::EPT_Bullet;

	FProjectileData* SetDataRow(const FName& Name);

	FName GetDataRowName(EProjectileType Type);

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void FireInDirection(const FVector& ShootDirection);

	void SetProjectileParams();

	void SetProjectileType(EProjectileType Type);

	void DestrioyProjectile();

};
