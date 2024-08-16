// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ClickCountManager.h"
#include <Kismet\GameplayStatics.h>
#include "Blueprint/UserWidget.h"
//#include <Gameplay\ClickCountViewManager.h>
#include <Character/MyPlayerCharacter.h>

// Sets default values
AClickCountManager::AClickCountManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ViewManager = CreateDefaultSubobject<UClickCountViewManager>(TEXT("View Manager"));
}

// Called when the game starts or when spawned
void AClickCountManager::BeginPlay()
{
	Super::BeginPlay();
	RegisterEvents();
}

void AClickCountManager::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	EventUpdateClickUI.Clear();
	EventUpdateMoveForwardUI.Clear();
	EventUpdateMoveBackwardUI.Clear();
	EventUpdateMoveLeftUI.Clear();
	EventUpdateMoveRightUI.Clear();
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
	EventUpdateClickUI.Broadcast(ClickCount);
}

void AClickCountManager::OnPlayerMoveForward()
{
	MoveForwardCount++;
	EventUpdateMoveForwardUI.Broadcast(MoveForwardCount);
}

void AClickCountManager::OnPlayerMoveBackward()
{
	MoveBackwardCount++;
	EventUpdateMoveBackwardUI.Broadcast(MoveBackwardCount);
}

void AClickCountManager::OnPlayerMoveRight()
{
	MoveRightCount++;
	EventUpdateMoveRightUI.Broadcast(MoveRightCount);
}

void AClickCountManager::OnPlayerMoveLeft()
{
	MoveLeftCount++;
	EventUpdateMoveLeftUI.Broadcast(MoveLeftCount);
}

