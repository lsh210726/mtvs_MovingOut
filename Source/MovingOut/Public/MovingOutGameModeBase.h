// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoxCountWidget.h"
#include "MovingOutGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API AMovingOutGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	 
	virtual void BeginPlay() override;

protected:

   TSubclassOf<UBoxCountWidget> MainHUDWidgetClass;
	UBoxCountWidget*MainHUDWidget;

public:
	AMovingOutGameModeBase();
	  
};
