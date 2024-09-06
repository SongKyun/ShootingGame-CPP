// Fill out your copyright notice in the Description page of Project Settings.


#include "CShootGameMode.h"
#include "Blueprint/UserWidget.h"
#include "CMainUI.h"


ACShootGameMode::ACShootGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACShootGameMode::Tick(float DeltaTime)
{
	FString stateStr = UEnum::GetValueAsString(myState);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *stateStr);

	Super::Tick(DeltaTime);
	switch (myState)
	{
	case EShootGameState::Title:
		Title();
		break;
	case EShootGameState::Ready:
		Ready();
		break;
	case EShootGameState::Start:
		Start();
		break;
	case EShootGameState::Playing:
		Playing();
		break;
	case EShootGameState::Pause:
		Pause();
		break;
	case EShootGameState::Gameover:
		Gameover();
		break;
	}
}

void ACShootGameMode::BeginPlay()
{
	Super::BeginPlay();

	mainUI = CreateWidget<UCMainUI>(GetWorld(), mainUIWidget);
	if (mainUI)
	{
		mainUI->AddToViewport();
	}

	// �Է¸�带 UI �� �������ֱ�
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void ACShootGameMode::Title()
{
}

// �����ð� ������ ���¸� Start�� �ٲ۴�.
void ACShootGameMode::Ready()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > ReadyDelayTime)
	{
		currentTime = 0;
		myState = EShootGameState::Start;
		mainUI->ChangeToStart();
	}
}

// �����ð� ������ ���¸� Playing�� �ٲ۴�.
void ACShootGameMode::Start()
{
	{
		currentTime += GetWorld()->DeltaTimeSeconds;
		if (currentTime > StartDelayTime)
		{
			currentTime = 0;
			myState = EShootGameState::Playing;
			mainUI->ChangeToPlaying();
		}
	}
}

void ACShootGameMode::Playing()
{
}

void ACShootGameMode::Pause()
{

}

void ACShootGameMode::Gameover()
{
}