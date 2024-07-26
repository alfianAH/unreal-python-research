// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ClickCountManager.h"
#include <Kismet\GameplayStatics.h>
#include <Character/MyPlayerCharacter.h>

// Sets default values
AClickCountManager::AClickCountManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClickCountManager::BeginPlay()
{
	Super::BeginPlay();
	RegisterEvents();
}

// Called every frame
void AClickCountManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClickCountManager::RegisterEvents()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	AMyPlayerCharacter* MyPlayerCharacter = Cast<AMyPlayerCharacter>(PlayerCharacter);

	if (MyPlayerCharacter == nullptr)
	{
		return;
	}

	MyPlayerCharacter->EventOnPlayerClick.AddUObject(this, &AClickCountManager::OnPlayerClick);
	MyPlayerCharacter->EventOnPlayerMoveForward.AddUObject(this, &AClickCountManager::OnPlayerMoveForward);
	MyPlayerCharacter->EventOnPlayerMoveBackward.AddUObject(this, &AClickCountManager::OnPlayerMoveBackward);
	MyPlayerCharacter->EventOnPlayerMoveRight.AddUObject(this, &AClickCountManager::OnPlayerMoveRight);
	MyPlayerCharacter->EventOnPlayerMoveLeft.AddUObject(this, &AClickCountManager::OnPlayerMoveLeft);
}

void AClickCountManager::OnPlayerClick()
{
	ClickCount++;
}

void AClickCountManager::OnPlayerMoveForward()
{
}

void AClickCountManager::OnPlayerMoveBackward()
{
}

void AClickCountManager::OnPlayerMoveRight()
{
}

void AClickCountManager::OnPlayerMoveLeft()
{
}

