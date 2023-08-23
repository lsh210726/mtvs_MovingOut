// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "MovingOutCharacter.h"

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	btn_NextMap->OnClicked.AddDynamic(this, &ULobbyWidget::OnClickInGame);
}


void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<AMovingOutCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingOutCharacter::StaticClass()));
}




void ULobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

void ULobbyWidget::OnClickInGame()
{
	//player->ServerCountPlayer();
	//GetWorld()->ServerTravel("/Game/Map/MovingTest?Listen", true);
	GetWorld()->ServerTravel("/Game/Map/Lee_Moving2?Listen", true);
}
