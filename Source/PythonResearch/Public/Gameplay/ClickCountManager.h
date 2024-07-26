// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClickCountManager.generated.h"

UCLASS()
class PYTHONRESEARCH_API AClickCountManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClickCountManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Click Count")
	int ClickCount = 0;

private:
	void RegisterEvents();

	UFUNCTION()
	void OnPlayerClick();
	
	UFUNCTION()
	void OnPlayerMoveForward();
	
	UFUNCTION()
	void OnPlayerMoveBackward();
	
	UFUNCTION()
	void OnPlayerMoveRight();
	
	UFUNCTION()
	void OnPlayerMoveLeft();
};
