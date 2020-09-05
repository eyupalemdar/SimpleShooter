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
	// Silah namlusuna efekt yerleþtir
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Bu silahý kullanan Pawn (Kullanýcý) ve onun Controller'ýný bul
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	// Kullanýcýnýn ViewPoint bilgisini ubl. (Ekrana bakýþ noktasý)
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// Merminin gidebileceði son noktayý hesapla
	FVector EndLocation = Location + Rotation.Vector() * MaxBulletRange;

	// Baþlangýç ve Bitiþ noktasý arasýnda bir LineTrace oluþtur ve 
	// bak bakalým verilen Channel'a uygun olarak herhangi birþeye çarpýyor mu?
	FHitResult Hit;
	bool bSuccessfulHit = GetWorld()->LineTraceSingleByChannel(
		Hit, Location, EndLocation, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccessfulHit)
	{
		FVector ShotDirection = -Rotation.Vector();
		// Merminin çarptýðý noktada efekt oluþtur.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		
		// Merminin çarptýðý þey bir Aktör mü?
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			// Aktörse ona Damage uygula
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}