// © 2020-2021 AlemdarLabs All Rights Are Reserved


#include "KillEmAllGameMode.h"


void AKillEmAllGameMode::PawnKilled(AActor* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));
}