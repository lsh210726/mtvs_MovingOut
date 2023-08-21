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

	virtual void Tick(float DeltaSeconds) override;
	
protected:

   TSubclassOf<UBoxCountWidget> MainHUDWidgetClass;
	UBoxCountWidget*MainHUDWidget;

public:
	AMovingOutGameModeBase();
	virtual void PostLogin(APlayerController* NewPlayer);

	UFUNCTION()
	void CountPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 playerNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bplayerMax = false;

	UFUNCTION( BlueprintCallable)
	void EnterMainMap();
};
