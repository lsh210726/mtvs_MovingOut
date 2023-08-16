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

//�߰�
void UBoxCountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//2. ATruckTriggerBox() �����κ��� ã��
	Truck = Cast<ATruckTriggerBox>(UGameplayStatics::GetActorOfClass(GetWorld(), ATruckTriggerBox::StaticClass()));

}




void UBoxCountWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 3. ATruckTriggerBox �ȿ� �ִ� count �� count_Text ������ ���ε��ϱ�
	// �÷��̾��� �������� ���� ����
	if (Truck)
	{
		Count_Text->SetText(FText::AsNumber(Truck->count));
	}
}