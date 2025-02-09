#pragma once

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	EPT_Bullet UMETA(DisplayName = "Bullet"),
	EPT_Rocket UMETA(DisplayName = "Rocket"),

	EPT_MAX UMETA(DisplayName = "DefaultMAX")
};