// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxCountWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API UBoxCountWidget : public UUserWidget
{
	GENERATED_BODY()

   UPROPERTY(EditAnywhere, Category = MySettings)
   TSubclassOf<class UBoxCountWidget> Countwidget;

   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* Count_Text;
   
   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* Slice_Text;
   
   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* MaxCount_Text;

	
};
