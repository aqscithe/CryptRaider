// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CryptRaiderHUD.generated.h"

UCLASS()
class ACryptRaiderHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACryptRaiderHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

