// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerInputEvent)

class AGameEventManager;
class UInputMappingContext;
class UInputDataConfig;

UCLASS()
class PYTHONRESEARCH_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FPlayerInputEvent EventOnPlayerClick;
	FPlayerInputEvent EventOnPlayerMoveForward;
	FPlayerInputEvent EventOnPlayerMoveBackward;
	FPlayerInputEvent EventOnPlayerMoveRight;
	FPlayerInputEvent EventOnPlayerMoveLeft;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player Character | Inputs")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Player Character | Inputs")
	UInputDataConfig* InputActions;

private:
	void RegisterInputMappingContext();
	
	void OnPlayerClick();
	void OnPlayerMoveForward();
	void OnPlayerMoveBackward();
	void OnPlayerMoveRight();
	void OnPlayerMoveLeft();
};
