// © 2020-2021 AlemdarLabs All Rights Are Reserved


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	if (AIOwner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(AIOwner->GetPawn());
	if (ShooterCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ShooterCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}