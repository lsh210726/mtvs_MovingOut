// Fill out your copyright notice in the Description page of Project Settings.


#include "MoivingOutGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/PlayerController.h"

UMoivingOutGameInstance::UMoivingOutGameInstance()
{
	//추후에 각 계정별 이름으로 변경예정
	mySessionName = TEXT("Eunchae");
}

void UMoivingOutGameInstance::Init()
{
	Super::Init();

	//onlinesubsystem instance를 get()으로 받아와서 확인하기 
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//온라인 세션 인터페이스 API 접근용 인스턴스 가져오기
		sessionInterface = subsys->GetSessionInterface();

		//createsession 이 성공적으로 진행되면 처리할 델리게이트 함수지정(세션이베트 함수 바인딩하기)
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMoivingOutGameInstance::OnCreateMySession);

		//JoinSession 이 성공적으로 진행되면 Join 이벤트 함수처리
		/*sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMoivingOutGameInstance::OnJoinMySession);*/

		//// 바로 createsession을 하면 맵 로딩하는데 시간이걸려생성이 안됨으로 timer로 시간을 벌어둠
		//FTimerHandle createHandler;
		//GetWorld()->GetTimerManager().SetTimer(createHandler, this, &UMoivingOutGameInstance::CreateSession, 1, false);
	}
}

void UMoivingOutGameInstance::CreateSession()
{	
	//session 생성시 설정요소 결정
	FOnlineSessionSettings sessionsettings;

	//1. LAN 연결인지 Dedicated 연결인지 설정한다.
	//deicated 연결 X -> listenserver 이용
	sessionsettings.bIsDedicated = false;
	//Lan 연결 O
	//sessionSettings.bIsLANMatch = true;
	//IOnlineSubsystem.Get()->GetSubsystemName() ==NULL 이면 랜 아니면 스팀
	sessionsettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//2. 검색 가능한 방으로 설정한다.
	sessionsettings.bShouldAdvertise = true;

	//3. 자기 정보를 전달될수 있게 할것인지 결정한다.
	sessionsettings.bUsesPresence = true;

	//4. 다른유저의 중간입장을 허용할수있게 한다.(bAllowJoinInProgress)  
	//   bAllowJoinViaPresence-> 친구가 하고있는게임 혹은 세션에 확인이 되면 참여할수 있게 한다.
	sessionsettings.bAllowJoinInProgress = true;
	sessionsettings.bAllowJoinViaPresence = true;

	//5. 입장 가능 인원을 설정한다.
	sessionsettings.NumPublicConnections = 4;
	
	//세션이 성공적으로 만들어졌는지 확인
	bool isSuccess = sessionInterface->CreateSession(0, FName("MovingOutTest Room"), sessionsettings);
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Fail"));
}

void UMoivingOutGameInstance::OnCreateMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		//세션이 만들어진 후 이동할 레벨 경로 지정
		//GetWorld()->ServerTravel("/Game/Map/KIM_Moving?Listen", true);
		GetWorld()->ServerTravel("/Game/Map/KIM_Moving?Listen", true);
	}
}

//void UMoivingOutGameInstance::JoinMySession()
//{
//	//세션 리스트를 찾아서
//	TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;
//
//
//	// 그중 아래와 같은 세션을 찾아서 조인하기
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
			//join된 세션 호스트의 serverTravel 된 맵주소를 받아온다.
			
			//FString url = "192.168.0.58";
			FString url = "192.168.0.76";
			//FString url = "192.168.0.58:7777";
			//FString url = "125.132.216.155:7777";
			//FString url = "192.168.0.217:7777";
			//session네임을 받으면 session 주소를 찾음
			sessionInterface->GetResolvedConnectString(sessionName, url);
			UE_LOG(LogTemp, Warning, TEXT("Connection URL : %s"), *url);

			// 주소를 잘 받았다면 해당 맵으로 이동
			if (!url.IsEmpty())
			{
				//레벨 이동
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

