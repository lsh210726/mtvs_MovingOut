// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TruckTriggerBox.generated.h"

UCLASS()
class MOVINGOUT_API ATruckTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATruckTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Truck")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Truck")
	class UStaticMeshComponent* BodyMesh;

	//유효한 가구 넣은 횟수
	UPROPERTY(EditAnywhere)
	int32 count;

	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

};
