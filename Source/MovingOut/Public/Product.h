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

	//Ʈ���� �ִ� ��ȿ�� �ڽ����� Ȯ���ϱ�
	UPROPERTY(EditAnywhere, Category="Prop")
	bool bValidProp = false;

	

};
