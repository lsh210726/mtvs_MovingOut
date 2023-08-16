// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxCountWidget.h"
#include <Kismet/GameplayStatics.h>
#include "TruckTriggerBox.h"
#include "MovingOutCharacter.h"
#include <UMG/Public/Components/TextBlock.h>


void UBoxCountWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

//추가
void UBoxCountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//2. ATruckTriggerBox() 레벨로부터 찾기
	Truck = Cast<ATruckTriggerBox>(UGameplayStatics::GetActorOfClass(GetWorld(), ATruckTriggerBox::StaticClass()));

}




void UBoxCountWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 3. ATruckTriggerBox 안에 있는 count 를 count_Text 값으로 바인딩하기
	// 플레이어의 프랍개수 정보 갱신
	if (Truck)
	{
		Count_Text->SetText(FText::AsNumber(Truck->count));
	}
}