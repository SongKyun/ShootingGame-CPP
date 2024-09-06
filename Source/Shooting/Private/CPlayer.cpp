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

	BoxComp->SetBoxExtent(FVector(50)); // 1 개만 넣으면 뒤에 다 똑같이 들어간다
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));

	// 에셋 등록
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		TempMesh(TEXT("/ Script / Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// 에셋이 정상 로드 되면
	if (TempMesh.Succeeded())
	{
		// 스테틱메시 할당
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// 머티리얼 로드하기
	ConstructorHelpers::FObjectFinder<UMaterialInterface>
		TempMat(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Basic_Wall.M_Basic_Wall'"));

	if (TempMat.Succeeded())
	{
		// 머터리얼 할당
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

	// 게임의 상태가 Ready, Start, Playing 일때만 이동가능
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}
	
	// 오른쪽 이동하기
	// 등속운동
	// P = P0 + vt

	//FVector vt = FVector::RightVector * 500 * DeltaTime;
	//FVector vt = FVector::LeftVector * 500 * DeltaTime;

	//FVector vt = FVector::DownVector * 500 * DeltaTime;

	// 대각선 이동 벡터를 생성합니다 (오른쪽 아래 방향).
	//FVector vt = (FVector::RightVector + FVector::DownVector).GetSafeNormal() * speed * DeltaTime;

	FVector P0 = GetActorLocation();
	// 사용자 입력에 따라 이동하고 싶다.
	// 1. 사용자의 입력을 받아야 한다
	// 2. 방향이 필요하다
	FVector Direction(0, h, v);
	// 3. 해당 방향으로 운동하고 싶다
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
	// 게임의 상태가 Ready, Start, Playing 일때만 이동가능
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

	// 이미 pause 상태라면 
	if (gm->myState == EShootGameState::Pause)
	{
		// pause를 플레잉으로 변경
		gm->myState = EShootGameState::Playing;
		// pause 풀어주자
		UGameplayStatics::SetGamePaused(GetWorld(), false);

	}
	else if (gm->myState == EShootGameState::Playing)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		gm->myState = EShootGameState::Pause;
	}
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
