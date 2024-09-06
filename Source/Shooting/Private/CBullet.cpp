// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	BoxComp->SetBoxExtent(FVector(50)); // 1 ���� ������ �ڿ� �� �Ȱ��� ����
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));

	// ���� ���
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		TempMesh(TEXT("/ Script / Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// ������ ���� �ε� �Ǹ�
	if (TempMesh.Succeeded())
	{
		// ����ƽ�޽� �Ҵ�
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// ��Ƽ���� �ε��ϱ�
	ConstructorHelpers::FObjectFinder<UMaterialInterface>
		TempMat(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Basic_Wall.M_Basic_Wall'"));

	if (TempMat.Succeeded())
	{
		// ���͸��� �Ҵ�
		BodyMesh->SetMaterial(0, TempMat.Object);
	}

	BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation() + GetActorUpVector() * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

