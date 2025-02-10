#include "Items.h"

// Sets default values
AItems::AItems()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}

void AItems::BeginPlay()
{
	Super::BeginPlay();
}

void AItems::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed) != 0.0f)
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * _deltaTime, 0.0f));
	}
}

void AItems::ResetActionPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItems::GetRotationSpeed() const
{
	return RotationSpeed;
}

