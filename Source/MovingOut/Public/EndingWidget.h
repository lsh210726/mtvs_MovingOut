// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API UEndingWidget : public UUserWidget
{
	GENERATED_BODY()
	

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	//class UTextBlock* Count_Text;

	////유효한 가구 넣은 횟수
	//UPROPERTY(EditAnywhere)
	//int32 count;

	//UFUNCTION()
	//void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
