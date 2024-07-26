// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class PYTHONRESEARCH_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditDefaultsOnly)
	UInputAction* Click;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveForeward;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveBackward;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveRight;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveLeft;
};
