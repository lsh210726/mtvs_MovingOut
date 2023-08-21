// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Product.generated.h"

UCLASS()
class MOVINGOUT_API AProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Prop")
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Prop")
	class UStaticMeshComponent* BodyMesh;

	//����������Ʈ ����
	UPROPERTY(VisibleAnywhere,Category="prop")
	class UWidgetComponent* WidGetComp;

	//Ʈ���� �ִ� ��ȿ�� �ڽ����� Ȯ���ϱ�
	UPROPERTY(EditAnywhere, Category="Prop")
	bool bValidProp = false;

	//true1 false2 �� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Prop")
	bool PropUI_1 = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
   FVector prevVelocity;

   UPROPERTY(EditAnywhere, Category=prop)
   class USoundBase* productSound;

   	bool bDoOnce=true; //�ο½�
	//Ÿ�̸�
	FTimerHandle GravityTimerHandle;
	float GravityTime=0.5f;

	//�Ҹ�����
	UPROPERTY(EditAnywhere, Category = prop)
	class USoundAttenuation* AttenuationSettings;

	//��Ʈ�̺�Ʈ
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
