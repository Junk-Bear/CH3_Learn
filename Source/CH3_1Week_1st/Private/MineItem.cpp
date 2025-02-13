// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.f;
	ExplosionDamage = 30.f;
	bHasExploded = false;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

	ItemType = "Mine";
}

void AMineItem::ActivateItem(AActor* Activator)
{
	if (bHasExploded) return;

	bHasExploded = true;
	Super::ActivateItem(Activator);
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay, false);
}

void AMineItem::Explode()
{
	UParticleSystemComponent* ParticleSystem = nullptr;
	if (ExplosionParticle)
	{
		ParticleSystem = UGameplayStatics::SpawnEmitterAtLocation (
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation (
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
		);
	}


	TArray<AActor*> OverlapingActors;
	ExplosionCollision->GetOverlappingActors(OverlapingActors);

	for (AActor* Actor : OverlapingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(Actor, ExplosionDamage, nullptr, this, UDamageType::StaticClass());
		}
	}
	DestroyItem();

	if (ParticleSystem)
	{
		FTimerHandle DestroyParticleTimerHandle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[ParticleSystem]()
			{
				ParticleSystem->DestroyComponent();
			},
			1.0f,
			false
		);
	}
}
