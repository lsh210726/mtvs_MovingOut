// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "PlayerBaseComponent.h"
#include "Product.h"
#include "Player_Move.h"
#include <kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "PropOne_UI.h"
#include "PropTwo_UI.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <EngineUtils.h>
#include "MovingOutGameModeBase.h"
#include <Components/BoxComponent.h>

// Sets default values
AMovingOutCharacter::AMovingOutCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    /*Camera*/
    //ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
    //ViewCamera->SetupAttachment(CameraBoom);
    //playerComp = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("Base Component"));
    playerMove = CreateDefaultSubobject<UPlayer_Move>(TEXT("PlayerMove"));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
    boxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovingOutCharacter::BeginPlay()
{
    
    Super::BeginPlay();
    //����ڵ�
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MovingOutContext, 0);
        }
    }
    boxComp->OnComponentBeginOverlap.AddDynamic(this, &AMovingOutCharacter::OnComponentBeginOverlap);
    boxComp->OnComponentEndOverlap.AddDynamic(this, &AMovingOutCharacter::OnComponentEndOverlap);


    //prop->SetVisibility(ESlateVisibility::Hidden);


    /*FTimerHandle changCamera;
    GetWorldTimerManager().SetTimer(changCamera, this, &AMovingOutCharacter::ChangeCamera, 1.0f, false);

    /*if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {
       pc = Cast<AMovingOutPlayerController>(GetController());
       pc->Possess(this);
    }

    if (HasAuthority())
    {

    }*/
    
}

// Called every frame
void AMovingOutCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GrabObjectContinue();

   
}

// Called to bind functionality to input
void AMovingOutCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Move �̵�

    /*UEnhancedInputComponent* inputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (inputComp != nullptr)
    {
       inputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
    }*/

    //onInputBindingDelegate.Broadcast(PlayerInputComponent);
    playerMove->SetupInputBinding(PlayerInputComponent);

    ////���ε�
    //playerComp->SetupInputBinding(PlayerInputComponent);
    ////PlayerInputComponent�� UEnhancedInputComponent Ÿ������ ����ȯ
    //if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    //{      
    //EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
    //EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Jump);

     //1,2������ ���� UIǥ�� ��ǲ��
    auto pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    //���ε�
    //playerComp->SetupInputBinding(PlayerInputComponent);
    //PlayerInputComponent�� UEnhancedInputComponent Ÿ������ ����ȯ
    if (pInput)
    {
        pInput->BindAction(SwitchUIAction, ETriggerEvent::Started, this, &AMovingOutCharacter::OnToggleUI);
        pInput->BindAction(SwitchUIAction, ETriggerEvent::Completed, this, &AMovingOutCharacter::OffToggleUI);
    }

    //�̽��� �ڵ�
    PlayerInputComponent->BindAction(TEXT("GrabObject"), IE_Pressed, this, &AMovingOutCharacter::GrabObjectStart);
    PlayerInputComponent->BindAction(TEXT("GrabObject"), IE_Released, this, &AMovingOutCharacter::GrabObjectEnd);
    PlayerInputComponent->BindAction(TEXT("ShootObject"), IE_Pressed, this, &AMovingOutCharacter::ShootObject);
}


void AMovingOutCharacter::Move(const FInputActionValue& value)
{
    //move�Լ�(������) ����
    //const FVector2D movementvector = value.Get<FVector2D>();
    ////const frotator rotation = controller->getcontrolrotation();
    ////const frotator yawrotation(0.f, rotation.yaw, 0.f); //�¿�
    //const FVector forwarddirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::X); //�չ���
    //AddMovementInput(forwarddirection, movementvector.Y); //���Ĺ� ������
    //const FVector rightdirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::Y); //�����ʹ���
    //AddMovementInput(rightdirection, movementvector.X); //�¿� ������
}



//void AMovingOutCharacter::Jump()
//{
//Super::Jump();*/ //Character.h�� �ִ� Jump���.
//}


void AMovingOutCharacter::OnToggleUI()
{
    //UE_LOG(LogTemp,Warning,TEXT("dddddddd"));

    //���忡 �ִ� Product �θ�Ŭ������ ���� Actor���� ��� ã�´�
    //�迭�� ��������
    /**/TArray<AActor*> arrOutActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProduct::StaticClass(), arrOutActors);
    //�迭�� ���� ������ AProduct ĳ��Ʈ
    for (AActor* actor : arrOutActors) //��̿��� �ϳ��ϳ� �ҷ��� ���� ���ְڴ�
    {
        AProduct* prop = Cast<AProduct>(actor); //AProduct ĳ��Ʈ

        if (prop != nullptr && prop->bValidProp == false)
        {//ĳ��Ʈ�� true��
            prop->WidGetComp->SetVisibility(true);
            prop->BodyMesh->SetRenderCustomDepth(true);
        }
    }
    /*for (TActorIterator<AProduct> It(GetWorld()); It; ++It)
    {
       AProduct* spawn = *It;
       spawn->WidGetComp->SetVisibility(true);
    }*/
}
void AMovingOutCharacter::OffToggleUI()
{
    //���忡 �ִ� Product �θ�Ŭ������ ���� Actor���� ��� ã�´�
    //�迭�� ��������
    /**/TArray<AActor*> arrOutActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProduct::StaticClass(), arrOutActors);
    //�迭�� ���� ������ AProduct ĳ��Ʈ
    for (AActor* actor : arrOutActors)
    {
        AProduct* prop = Cast<AProduct>(actor);
        if (prop != nullptr && prop->bValidProp == false)//���� ĳ��Ʈ�� true��
        {
            prop->WidGetComp->SetVisibility(false);
            prop->BodyMesh->SetRenderCustomDepth(false);
        }
    }
    
    //    else
    //    {
    //        // UI ������ ����Ʈ���� �����մϴ�.
    //        livingSwitchUI_One->RemoveFromParent();
    //        livingSwitchUI_OneInstance = nullptr;
}

void AMovingOutCharacter::ServerCountPlayer_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ServerCountPlayer"));
	gm = Cast<AMovingOutGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("gggg"));
		gm->CountPlayer();
	}
}

void AMovingOutCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AProduct* prop = Cast<AProduct>(OtherActor);
   // prop�̶��
   
   if (prop && bGrab == false)
   //if (prop && prop->bValidProp && bCountCheck == true)
   {
      prop->BodyMesh->SetRenderCustomDepth(true);
   }
}

void AMovingOutCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   AProduct* prop = Cast<AProduct>(OtherActor);
   // prop�̶��
   if (prop)
   //if (prop && prop->bValidProp && bCountCheck == true)
   {
       prop->BodyMesh->SetRenderCustomDepth(false);
   }
}

void AMovingOutCharacter::GrabObjectStart_Implementation()
 {

}

void AMovingOutCharacter::GrabObjectEnd_Implementation()
{

}

void AMovingOutCharacter::GrabObjectContinue_Implementation()
{

}

void AMovingOutCharacter::ShootObject_Implementation()
{

}

/*void AMovingOutCharacter::ChangeCamera()
{
   if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {

      movingoutCamera = Cast<AOnePersonCamera>(UGameplayStatics::GetActorOfClass(this, AOnePersonCamera::StaticClass()));
      pc = Cast<AMovingOutPlayerController>(GetController());
      pc->SetViewTarget(movingoutCamera);
   }
}*/