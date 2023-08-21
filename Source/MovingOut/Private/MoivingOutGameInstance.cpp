// Fill out your copyright notice in the Description page of Project Settings.


#include "MoivingOutGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/PlayerController.h"

UMoivingOutGameInstance::UMoivingOutGameInstance()
{
	//���Ŀ� �� ������ �̸����� ���濹��
	mySessionName = TEXT("Eunchae");
}

void UMoivingOutGameInstance::Init()
{
	Super::Init();

	//onlinesubsystem instance�� get()���� �޾ƿͼ� Ȯ���ϱ� 
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//�¶��� ���� �������̽� API ���ٿ� �ν��Ͻ� ��������
		sessionInterface = subsys->GetSessionInterface();

		//createsession �� ���������� ����Ǹ� ó���� ��������Ʈ �Լ�����(�����̺�Ʈ �Լ� ���ε��ϱ�)
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMoivingOutGameInstance::OnCreateMySession);

		//JoinSession �� ���������� ����Ǹ� Join �̺�Ʈ �Լ�ó��
		/*sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMoivingOutGameInstance::OnJoinMySession);*/

		//// �ٷ� createsession�� �ϸ� �� �ε��ϴµ� �ð��̰ɷ������� �ȵ����� timer�� �ð��� �����
		//FTimerHandle createHandler;
		//GetWorld()->GetTimerManager().SetTimer(createHandler, this, &UMoivingOutGameInstance::CreateSession, 1, false);
	}
}

void UMoivingOutGameInstance::CreateSession()
{	
	//session ������ ������� ����
	FOnlineSessionSettings sessionsettings;

	//1. LAN �������� Dedicated �������� �����Ѵ�.
	//deicated ���� X -> listenserver �̿�
	sessionsettings.bIsDedicated = false;
	//Lan ���� O
	//sessionSettings.bIsLANMatch = true;
	//IOnlineSubsystem.Get()->GetSubsystemName() ==NULL �̸� �� �ƴϸ� ����
	sessionsettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//2. �˻� ������ ������ �����Ѵ�.
	sessionsettings.bShouldAdvertise = true;

	//3. �ڱ� ������ ���޵ɼ� �ְ� �Ұ����� �����Ѵ�.
	sessionsettings.bUsesPresence = true;

	//4. �ٸ������� �߰������� ����Ҽ��ְ� �Ѵ�.(bAllowJoinInProgress)  
	//   bAllowJoinViaPresence-> ģ���� �ϰ��ִ°��� Ȥ�� ���ǿ� Ȯ���� �Ǹ� �����Ҽ� �ְ� �Ѵ�.
	sessionsettings.bAllowJoinInProgress = true;
	sessionsettings.bAllowJoinViaPresence = true;

	//5. ���� ���� �ο��� �����Ѵ�.
	sessionsettings.NumPublicConnections = 4;
	
	//������ ���������� ����������� Ȯ��
	bool isSuccess = sessionInterface->CreateSession(0, FName("MovingOutTest Room"), sessionsettings);
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Fail"));
}

void UMoivingOutGameInstance::OnCreateMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		//������ ������� �� �̵��� ���� ��� ����
		//GetWorld()->ServerTravel("/Game/Map/KIM_Moving?Listen", true);
		GetWorld()->ServerTravel("/Game/Map/KIM_Moving?Listen", true);
	}
}

//void UMoivingOutGameInstance::JoinMySession()
//{
//	//���� ����Ʈ�� ã�Ƽ�
//	TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;
//
//
//	// ���� �Ʒ��� ���� ������ ã�Ƽ� �����ϱ�
//	sessionInterface->JoinSession(0, FName("MovingOutTest Room"), sessionSearch->SearchResults[0]);
//}

void UMoivingOutGameInstance::OnJoinMySession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), result == EOnJoinSessionCompleteResult::Success ? *FString::Printf(TEXT("Success : %s"), *sessionName.ToString()) : *FString(TEXT("Failed")));

	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
	{
		//UE_LOG(LogTemp, Warning, TEXT("Success : %s"), *sessionName.ToString());

		APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

		if (playerCon != nullptr)
		{
			//join�� ���� ȣ��Ʈ�� serverTravel �� ���ּҸ� �޾ƿ´�.
			
			FString url = "192.168.0.58";
			//FString url = "192.168.0.58:7777";
			//FString url = "125.132.216.155:7777";
			//FString url = "192.168.0.217:7777";
			//session������ ������ session �ּҸ� ã��
			sessionInterface->GetResolvedConnectString(sessionName, url);
			UE_LOG(LogTemp, Warning, TEXT("Connection URL : %s"), *url);

			// �ּҸ� �� �޾Ҵٸ� �ش� ������ �̵�
			if (!url.IsEmpty())
			{
				//���� �̵�
				playerCon->ClientTravel(url, ETravelType::TRAVEL_Absolute);
			}

		}
	}
	break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("SessionIsFull"));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("SessionDoesNotExist"));
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("CouldNotRetrieveAddress"));
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("AlreadyInSession"));
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("UnknownError"));
		break;

	}
}

