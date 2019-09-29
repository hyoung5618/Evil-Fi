// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Evil_FiCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "../ProjectTile/Skills/TestFireSkill.h"

//////////////////////////////////////////////////////////////////////////
// AEvil_FiCharacter

AEvil_FiCharacter::AEvil_FiCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	static ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AssetSkill_1(TEXT("AnimSequence'/Game/Mannequin/Animations/Skill_Motion_1.Skill_Motion_1'")); //! 경로 입력
	if (AssetSkill_1.Succeeded())
		m_pAnimSequence_Skill_1 = AssetSkill_1.Object;         //! 시퀸스 변수 세팅
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEvil_FiCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEvil_FiCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEvil_FiCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEvil_FiCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEvil_FiCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEvil_FiCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEvil_FiCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AEvil_FiCharacter::OnResetVR);

	// Skill Key
	PlayerInputComponent->BindAction("Skill_1", IE_Pressed, this, &AEvil_FiCharacter::UseSkill_1);
	PlayerInputComponent->BindAction("Skill_2", IE_Pressed, this, &AEvil_FiCharacter::UseSkill_2);
	PlayerInputComponent->BindAction("Skill_3", IE_Pressed, this, &AEvil_FiCharacter::UseSkill_3);
	PlayerInputComponent->BindAction("Skill_4", IE_Pressed, this, &AEvil_FiCharacter::UseSkill_4);
}


void AEvil_FiCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEvil_FiCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AEvil_FiCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AEvil_FiCharacter::UseSkill_1()
{
	USkeletalMeshComponent* pSkelMeshComponent = GetMesh();
	if (pSkelMeshComponent == nullptr)
	{
		return;
	}

	UAnimInstance* pAnimInstance = pSkelMeshComponent->GetAnimInstance();
	if (pAnimInstance == nullptr)
	{
		return;
	}

	UAnimMontage* pAnimationMtg = pAnimInstance->PlaySlotAnimationAsDynamicMontage(m_pAnimSequence_Skill_1, TEXT("DefaultSlot"), 0.3f, 0.3f, 1.0f);
	if (pAnimationMtg != nullptr)
		PlayAnimMontage(pAnimationMtg, 1.0f);

	FTransform transform = GetTransform();

	FVector vFowardDir = transform.GetRotation().GetForwardVector();

	FVector vSpawnPos = transform.GetLocation() + vFowardDir * 100.f;
	transform.SetLocation(vSpawnPos);

	ATestFireSkill* pSpawnSkill = GetWorld()->SpawnActor<ATestFireSkill>(ATestFireSkill::StaticClass(), transform);
	if (pSpawnSkill != nullptr)
		pSpawnSkill->SetFireDirection(vFowardDir);

	FVector vLeftPos = vFowardDir + FVector::LeftVector;
	vSpawnPos = transform.GetLocation() + vLeftPos * 100.f;
	transform.SetLocation(vSpawnPos);

	pSpawnSkill = GetWorld()->SpawnActor<ATestFireSkill>(ATestFireSkill::StaticClass(), transform);
	if (pSpawnSkill != nullptr)
		pSpawnSkill->SetFireDirection(vLeftPos);

	FVector vRightPos = vFowardDir + FVector::RightVector;
	vSpawnPos = transform.GetLocation() + vRightPos * 100.f;
	transform.SetLocation(vSpawnPos);

	pSpawnSkill = GetWorld()->SpawnActor<ATestFireSkill>(ATestFireSkill::StaticClass(), transform);
	if (pSpawnSkill != nullptr)
		pSpawnSkill->SetFireDirection(vRightPos);
}

void AEvil_FiCharacter::UseSkill_2()
{

}

void AEvil_FiCharacter::UseSkill_3()
{

}

void AEvil_FiCharacter::UseSkill_4()
{

}

void AEvil_FiCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEvil_FiCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AEvil_FiCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEvil_FiCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
