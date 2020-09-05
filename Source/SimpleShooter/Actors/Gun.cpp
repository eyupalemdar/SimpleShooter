#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	// Silah namlusuna efekt yerle�tir
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Bu silah� kullanan Pawn (Kullan�c�) ve onun Controller'�n� bul
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	// Kullan�c�n�n ViewPoint bilgisini ubl. (Ekrana bak�� noktas�)
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// Merminin gidebilece�i son noktay� hesapla
	FVector EndLocation = Location + Rotation.Vector() * MaxBulletRange;

	// Ba�lang�� ve Biti� noktas� aras�nda bir LineTrace olu�tur ve 
	// bak bakal�m verilen Channel'a uygun olarak herhangi bir�eye �arp�yor mu?
	FHitResult Hit;
	bool bSuccessfulHit = GetWorld()->LineTraceSingleByChannel(
		Hit, Location, EndLocation, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccessfulHit)
	{
		FVector ShotDirection = -Rotation.Vector();
		// Merminin �arpt��� noktada efekt olu�tur.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		
		// Merminin �arpt��� �ey bir Akt�r m�?
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			// Akt�rse ona Damage uygula
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}