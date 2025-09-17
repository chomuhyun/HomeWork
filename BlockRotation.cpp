#include "BlockRotation.h"

ABlockRotation::ABlockRotation()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 90.0f;
}

// Called when the game starts or when spawned
void ABlockRotation::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlockRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, 0.0f , RotationSpeed * DeltaTime));
	}
}

