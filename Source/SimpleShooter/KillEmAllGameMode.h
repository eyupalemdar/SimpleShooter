// © 2020-2021 AlemdarLabs All Rights Are Reserved

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

};
