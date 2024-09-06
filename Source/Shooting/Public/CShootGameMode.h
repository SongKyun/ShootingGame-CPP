// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CShootGameMode.generated.h"

UENUM(BlueprintType)
enum class EShootGameState : uint8
{
	Title,
	Ready,
	Start,
	Playing,
	Pause,
	Gameover
};

UCLASS()
class SHOOTING_API ACShootGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACShootGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere, Category="Game")
	EShootGameState myState;

	void Title();
	void Ready();
	void Start();
	void Playing();
	void Pause();
	void Gameover();

	// « ø‰«— MainUI ¿ß¡¨
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<class UUserWidget> mainUIWidget;

	UPROPERTY()
	class UCMainUI* mainUI;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float ReadyDelayTime = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float StartDelayTime = 2;

	float currentTime = 0;
};