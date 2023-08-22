// Fill out your copyright notice in the Description page of Project Settings.


#include "Product.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundAttenuation.h"

// Sets default values
AProduct::AProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(10));*/

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	//BodyMesh->SetupAttachment(RootComponent);
	RootComponent=BodyMesh;

	//����������Ʈ ������ֱ�
	WidGetComp= CreateDefaultSubobject<UWidgetComponent>(TEXT("WidGetComp"));
	//��Ʈ�� �������� 
	WidGetComp->SetupAttachment(RootComponent);
	WidGetComp->SetRelativeLocation(FVector(1,1,1));
	WidGetComp->SetRelativeScale3D(FVector(1,1,1));

	BodyMesh->SetNotifyRigidBodyCollision(true);
	BodyMesh->OnComponentHit.AddDynamic(this, &AProduct::OnHit);
}

// Called when the game starts or when spawned
void AProduct::BeginPlay()
{
	Super::BeginPlay();
	WidGetComp->SetVisibility(false);
	
	if (HasAuthority())
	{
		auto owner = GetWorld()->GetFirstPlayerController();
		SetOwner(owner);
	}
}

// Called every frame
void AProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���ſ� ��ü ���� �Ҹ�
	FVector nowVelocity = BodyMesh->GetComponentVelocity();
	FVector v = nowVelocity - prevVelocity;
	if (BodyMesh->GetMass() > 51)
	{

		if (v.Size() > 30.0f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("Velo %f"), v.Size()));
			if (bDoOnce && AttenuationSettings != nullptr)
			{
				bDoOnce = false;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), productSound, BodyMesh->GetComponentLocation(), 1.0f, 1.0f, 0.0f, AttenuationSettings);
				GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						bDoOnce = true;
						// TimerHandle �ʱ�ȭ
						GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
					}), GravityTime, false);
			}
		}
	}

	prevVelocity = nowVelocity;
}

//������ ��ü �浹 �� �Ҹ� �߻�
void AProduct::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Do something with the hit result
	if (BodyMesh->GetMass() < 51)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("Velo %f"), BodyMesh->GetComponentVelocity().Length()));
		if (BodyMesh->GetComponentVelocity().Length() > 100)
		{
			if (bDoOnce && AttenuationSettings != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("Velo %f"), BodyMesh->GetComponentVelocity().Length()));
				bDoOnce = false;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), productSound, BodyMesh->GetComponentLocation(), 1.0f, 1.0f, 0.0f, AttenuationSettings);
				GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						bDoOnce = true;
						// TimerHandle �ʱ�ȭ
						GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
					}), GravityTime, false);
			}

		}
	}
}