// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"
#include "CShootGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPlayer::ACPlayer()
{
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
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������ ���°� Ready, Start, Playing �϶��� �̵�����
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}
	
	// ������ �̵��ϱ�
	// ��ӿ
	// P = P0 + vt

	//FVector vt = FVector::RightVector * 500 * DeltaTime;
	//FVector vt = FVector::LeftVector * 500 * DeltaTime;

	//FVector vt = FVector::DownVector * 500 * DeltaTime;

	// �밢�� �̵� ���͸� �����մϴ� (������ �Ʒ� ����).
	//FVector vt = (FVector::RightVector + FVector::DownVector).GetSafeNormal() * speed * DeltaTime;

	FVector P0 = GetActorLocation();
	// ����� �Է¿� ���� �̵��ϰ� �ʹ�.
	// 1. ������� �Է��� �޾ƾ� �Ѵ�
	// 2. ������ �ʿ��ϴ�
	FVector Direction(0, h, v);
	// 3. �ش� �������� ��ϰ� �ʹ�
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis inputs
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
	PlayerInputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &ACPlayer::PauseInput);
}

void ACPlayer::Horizontal(float Value)
{
	h = Value;
}

void ACPlayer::Vertical(float Value)
{
	v = Value;
}

void ACPlayer::Fire()
{
	// ������ ���°� Ready, Start, Playing �϶��� �̵�����
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}

	PlayFireSound();
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, GetActorLocation(), FRotator::ZeroRotator);
}

void ACPlayer::PauseInput()
{
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());

	// �̹� pause ���¶�� 
	if (gm->myState == EShootGameState::Pause)
	{
		// pause�� �÷������� ����
		gm->myState = EShootGameState::Playing;
		// pause Ǯ������
		UGameplayStatics::SetGamePaused(GetWorld(), false);

	}
	else if (gm->myState == EShootGameState::Playing)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		gm->myState = EShootGameState::Pause;
	}
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
