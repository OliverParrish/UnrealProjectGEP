// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudUI.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECT_API AHudUI : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;
	
private:
	
	UPROPERTY(EditAnywhere)
	class UTexture2D* Crosshair;
	
};
