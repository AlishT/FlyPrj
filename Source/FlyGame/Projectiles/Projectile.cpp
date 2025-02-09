

#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundAttenuation.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionBox);
	ProjectileMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_OverlapAll_Deprecated, ECollisionResponse::ECR_Ignore);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->SetUpdatedComponent(CollisionBox);
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	SetProjectileParams();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHit) return;

	if (ProjectileType == EProjectileType::EPT_Rocket)
	{
		CurrentTime += DeltaTime;

		if (CurrentTime >= DestroyTime)
		{
			Destroy();
		}
	}
}

FProjectileData* AProjectile::SetDataRow(const FName& Name)
{
	if (ProjectileDataTable)
	{
		return ProjectileDataTable->FindRow<FProjectileData>(FName(Name), "");
	}

	return nullptr;
}

FName AProjectile::GetDataRowName(EProjectileType Type)
{
	FName DataRowName = "None";

	switch (Type)
	{
	case EProjectileType::EPT_Bullet:
		DataRowName = "Bullet";
		break;
	case EProjectileType::EPT_Rocket:
		DataRowName = "Rocket";
		break;
	}

	return DataRowName;
}

void AProjectile::SetProjectileParams()
{
	FName DataRow = GetDataRowName(ProjectileType);

	FProjectileData* ProjectileDataRow = SetDataRow(DataRow);

	if (ProjectileDataRow)
	{
		Damage = ProjectileDataRow->Damage;
		ProjectileMovement->InitialSpeed = ProjectileDataRow->ProjectileSpeed;
		ProjectileMovement->MaxSpeed = ProjectileDataRow->ProjectileSpeed;
		ProjectileMesh->SetStaticMesh(ProjectileDataRow->ProjectileMesh);
		ImpactSound = ProjectileDataRow->ImpactSound;
		AirLoopSound = ProjectileDataRow->AirLoopSound;
		TrailSystem = ProjectileDataRow->TrailSystem;
		ImpactPartical = ProjectileDataRow->ImpactPartical;
	}
}

void AProjectile::SetProjectileType(EProjectileType Type)
{
	ProjectileType = Type;

	SetProjectileParams();

	if (AirLoopSound && LoopingSoundAttenuation)
	{
		AirLoopComponent = UGameplayStatics::SpawnSoundAttached(AirLoopSound, GetRootComponent(), FName(), GetActorLocation(), EAttachLocation::KeepWorldPosition, false, 1.f, 1.f, 0.f, LoopingSoundAttenuation, (USoundConcurrency*)nullptr, false);
	}

	if (TrailSystem)
	{
		TrailSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TrailSystem, GetRootComponent(), FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}
}

void AProjectile::DestrioyProjectile()
{
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
	}

	if (ImpactPartical)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactPartical, GetActorTransform());
	}

	if (ProjectileType != EProjectileType::EPT_Rocket)
	{
		Destroy();
	}

	bHit = true;

	if (ProjectileMesh)
	{
		ProjectileMesh->SetVisibility(false);
	}

	if (CollisionBox)
	{
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (TrailSystemComponent)
	{
		TrailSystemComponent->Deactivate();
	}

	if (AirLoopComponent)
	{
		AirLoopComponent->Deactivate();
	}
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetOwner())
	{
		AController* OwnerInstigator = GetOwner()->GetInstigatorController();
		UClass* DamageTypeClass = UDamageType::StaticClass();

		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
	}

	DestrioyProjectile();
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

