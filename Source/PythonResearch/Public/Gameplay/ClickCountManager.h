// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClickCountManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateUIEvent, int)

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

	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Click Count | Debug")
	int ClickCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Click Count | Debug")
	int MoveForwardCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Click Count | Debug")
	int MoveBackwardCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Click Count | Debug")
	int MoveLeftCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Click Count | Debug")
	int MoveRightCount = 0;
	
	//UPROPERTY(EditAnywhere)
	//class UClickCountViewManager* ViewManager;

	FUpdateUIEvent EventUpdateClickUI;
	FUpdateUIEvent EventUpdateMoveForwardUI;
	FUpdateUIEvent EventUpdateMoveBackwardUI;
	FUpdateUIEvent EventUpdateMoveLeftUI;
	FUpdateUIEvent EventUpdateMoveRightUI;

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
