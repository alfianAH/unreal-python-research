// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyPlayerCharacter.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Data/InputDataConfig.h>

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPlayerCharacter::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	
	EventOnPlayerClick.Clear();
	EventOnPlayerMoveForward.Clear();
	EventOnPlayerMoveBackward.Clear();
	EventOnPlayerMoveLeft.Clear();
	EventOnPlayerMoveRight.Clear();
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	RegisterInputMappingContext();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (InputActions == nullptr)
	{
		return;
	}

	Input->BindAction(InputActions->Click, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::OnPlayerClick);
	Input->BindAction(InputActions->MoveForward, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::OnPlayerMoveForward);
	Input->BindAction(InputActions->MoveBackward, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::OnPlayerMoveBackward);
	Input->BindAction(InputActions->MoveRight, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::OnPlayerMoveRight);
	Input->BindAction(InputActions->MoveLeft, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::OnPlayerMoveLeft);
}

void AMyPlayerCharacter::RegisterInputMappingContext()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
}

void AMyPlayerCharacter::OnPlayerClick()
{
	EventOnPlayerClick.Broadcast();
}

void AMyPlayerCharacter::OnPlayerMoveForward()
{
	EventOnPlayerMoveForward.Broadcast();
}

void AMyPlayerCharacter::OnPlayerMoveBackward()
{
	EventOnPlayerMoveBackward.Broadcast();
}

void AMyPlayerCharacter::OnPlayerMoveRight()
{
	EventOnPlayerMoveRight.Broadcast();
}

void AMyPlayerCharacter::OnPlayerMoveLeft()
{
	EventOnPlayerMoveLeft.Broadcast();
}

