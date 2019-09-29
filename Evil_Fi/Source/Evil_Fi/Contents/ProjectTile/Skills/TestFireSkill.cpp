// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFireSkill.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ConstructorHelpers.h"

ATestFireSkill::ATestFireSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	// 박스 형태의 충돌체 컴포넌트 생성
	m_pCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (m_pCollisionComponent != nullptr)
	{
		m_pCollisionComponent->InitBoxExtent(FVector::OneVector);
		m_pCollisionComponent->SetEnableGravity(false);
		m_pCollisionComponent->SetSimulatePhysics(true);
		m_pCollisionComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		RootComponent = m_pCollisionComponent;
	}

	// 메쉬 컴포넌트 생성
	m_pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (m_pStaticMeshComponent != nullptr)
	{
		m_pStaticMeshComponent->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeVisualAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
		if (cubeVisualAsset.Succeeded())
		{
			m_pStaticMeshComponent->SetStaticMesh(cubeVisualAsset.Object);
			m_pStaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			m_pStaticMeshComponent->SetWorldScale3D(FVector(0.25f));
		}
	}

	// 프로젝타일 무브먼트 컴포넌트 생성
	m_pProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	if (m_pProjectileMovementComponent != nullptr)
	{
		m_pProjectileMovementComponent->SetUpdatedComponent(m_pCollisionComponent);
		m_pProjectileMovementComponent->InitialSpeed = 1000.0f;
		m_pProjectileMovementComponent->MaxSpeed = 1000.0f;
		m_pProjectileMovementComponent->bRotationFollowsVelocity = true;
		m_pProjectileMovementComponent->bShouldBounce = true;
		m_pProjectileMovementComponent->Bounciness = 0.3f;
	}
}

void ATestFireSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestFireSkill::SetFireDirection(const FVector& shootDir)
{
	if (m_pProjectileMovementComponent != nullptr)
		m_pProjectileMovementComponent->Velocity = shootDir * m_pProjectileMovementComponent->InitialSpeed;
}
