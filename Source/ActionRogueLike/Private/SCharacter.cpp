// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	AddMovementInput(ControlRotator.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	// X == Forward
	// Y == Right
	// Z == Up

	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	// Use mesh to get hand location.
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	
	// Where to spawn this new actor.
	FTransform SpawnTransformMatrix(GetControlRotation(), HandLocation);

	// What kind of actor will be spawned.
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParameters);
}
