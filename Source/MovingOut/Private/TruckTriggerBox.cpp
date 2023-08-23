// Fill out your copyright notice in the Description page of Project Settings.


#include "TruckTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Product.h"
#include "Engine/Engine.h"
#include "MovingOutCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATruckTriggerBox::ATruckTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(100));

	//BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	//BodyMesh->SetupAttachment(RootComponent);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATruckTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ATruckTriggerBox::OnComponentBeginOverlap);

	if (HasAuthority())
	{
		auto owner = GetWorld()->GetFirstPlayerController();
		SetOwner(owner);
	}

	player = Cast<AMovingOutCharacter>(UGameplayStatics::GetActorOfClass(this, AMovingOutCharacter::StaticClass()));
}

// Called every frame
void ATruckTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//브랜치 추가

	if (count == 8)
	{	
		//엔딩위젯 걸린 맵으로 이동
		//GetWorld()->ServerTravel("/Game/Map/MovingTest?Listen", true);
		player->finalScore = count;
		player->bFinalGame = true;
		GetWorld()->ServerTravel("/Game/Map/EndingMap?Listen", true);
	}
}


void ATruckTriggerBox::ServerOnRep_CountUpdated()
{
	UE_LOG(LogTemp, Warning, TEXT("ServerOnRep_CountUpdated"));
	//prop이 가지고있는 bValidProp 이 true이면
	if (count < 15) {
	//	//유효횟수 추가
		count++;
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("ValidProp : %d"), count));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("It's Prop")));
	//MultiOnRep_CountUpdated();
}

void ATruckTriggerBox::MultiOnRep_CountUpdated_Implementation()
{
}



void ATruckTriggerBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//trucktiggerbox에 prop이 들어왔는지 확인
	AProduct* prop = Cast<AProduct>(OtherActor);

	// prop이라면
	if (prop && prop->bValidProp)
	{
		
		ServerOnRep_CountUpdated();
	}

}

void ATruckTriggerBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATruckTriggerBox, count);
}

