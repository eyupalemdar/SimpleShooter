// © 2020-2021 AlemdarLabs All Rights Are Reserved


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HUDScreen = CreateWidget(this, HUDScreenClass);
	if (HUDScreen)
	{
		HUDScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUDScreen)
	{
		HUDScreen->RemoveFromParent();
	}

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}