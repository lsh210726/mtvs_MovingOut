// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "OnePersonCamera.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API AOnePersonCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AOnePersonCamera();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	
public:

	UPROPERTY(EditAnywhere, Category="Camera")
	class AMovingOutCharacter* player;

	
};
