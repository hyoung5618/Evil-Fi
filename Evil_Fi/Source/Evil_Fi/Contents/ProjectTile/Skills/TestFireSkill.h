// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Contents/ProjectTile/ProjectTileBase.h"
#include "TestFireSkill.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

/**
 * 
 */
UCLASS()
class EVIL_FI_API ATestFireSkill : public AProjectTileBase
{
	GENERATED_BODY()
	
public:
	ATestFireSkill();

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetFireDirection(const FVector& shootDir);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_pCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = StaticMesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pStaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_pProjectileMovementComponent;
};
