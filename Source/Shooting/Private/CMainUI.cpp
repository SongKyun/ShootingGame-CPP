// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainUI.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "CShootGameMode.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UCMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	btn_GameStart->OnClicked.AddDynamic(this, &UCMainUI::OnGameStartBtnClicked);
}

void UCMainUI::OnGameStartBtnClicked()
{
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "Click!!!!!!");
	// 게임 상태를 Ready 로 전환하고 싶다.
	// 1. 게임모드가 있어야한다.
	auto gm = Cast<ACShootGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	// 2. 게임모드의 상태를 바꿔준다.
	if (gm)
	{
		gm->myState = EShootGameState::Ready;
		ReadyText->SetVisibility(ESlateVisibility::Visible);
	}

	TitleCanvas->SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

void UCMainUI::ChangeToStart()
{
	ReadyText->SetVisibility(ESlateVisibility::Hidden);
	StartText->SetVisibility(ESlateVisibility::Visible);
}

void UCMainUI::ChangeToPlaying()
{
	StartText->SetVisibility(ESlateVisibility::Hidden);
}

void UCMainUI::ChangeToGameover()
{
	GameOverText->SetVisibility(ESlateVisibility::Hidden);
	PlayAnimation(GameOverAnim);
}
