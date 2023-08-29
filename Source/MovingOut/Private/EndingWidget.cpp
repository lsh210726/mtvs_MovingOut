// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Product.h"

//void UEndingWidget::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	//trucktiggerbox에 prop이 들어왔는지 확인
//	AProduct* prop = Cast<AProduct>(OtherActor);
//
//	// prop이라면
//	if (prop)
//	{	
//		//prop이 가지고있는 bValidProp 이 true이면
//		if (prop->bValidProp && count < 3) {
//			//유효횟수 추가
//			count++;
//			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("ValidProp : %d"), count));
//		}
//		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("It's Prop")));
//	}
//}
