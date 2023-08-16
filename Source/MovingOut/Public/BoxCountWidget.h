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

	//�߰�
	public:	
	// Sets default values for this actor's properties
	virtual void NativeOnInitialized ();

	//�߰�
	public:	
	// ������ tick �̺�Ʈ �Լ� �߰�
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	//�߰�
	public:	

   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* Count_Text = 0;
   
   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* Slice_Text;
   
   UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
   class UTextBlock* MaxCount_Text;

   UPROPERTY()
   class ATruckTriggerBox* Truck;

  




};
