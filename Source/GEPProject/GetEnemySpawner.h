// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetEnemySpawner.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetEnemySpawner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GEPPROJECT_API IGetEnemySpawner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	class AEnemySpawner* GetEnemySpawner();
};
