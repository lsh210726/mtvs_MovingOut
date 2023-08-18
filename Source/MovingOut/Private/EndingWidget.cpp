// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Product.h"

void UEndingWidget::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//trucktiggerbox�� prop�� ���Դ��� Ȯ��
	AProduct* prop = Cast<AProduct>(OtherActor);

	// prop�̶��
	if (prop)
	{	
		//prop�� �������ִ� bValidProp �� true�̸�
		if (prop->bValidProp && count < 3) {
			//��ȿȽ�� �߰�
			count++;
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("ValidProp : %d"), count));
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("It's Prop")));
	}
}
