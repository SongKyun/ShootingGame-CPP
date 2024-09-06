// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CMainUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UCMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* TitleCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btn_GameStart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ReadyText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* StartText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* GameOverText;
	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* GameOverAnim;


	UFUNCTION()
	void OnGameStartBtnClicked();

	void ChangeToStart();
	void ChangeToPlaying();
	void ChangeToGameover();
};