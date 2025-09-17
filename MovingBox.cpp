#include "MovingBox.h"

AMovingBox::AMovingBox()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	FwdSpeed = 90.0f;
}

void AMovingBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Forward = GetActorForwardVector();

	if (FMath::IsNearlyZero(FwdSpeed)) return;

	float MovingTotal = FwdSpeed * DeltaTime * Reverse; // 현재 속도에서 리버스 변수 곱해서 방향 설정

	AddActorLocalOffset(Forward * MovingTotal); // 설정한 방향으로 이동

	CurrentDistance += MovingTotal; // 이동한 거리 계산

	if (CurrentDistance >= MaxDistance) //만약 현재 이동거리가 목표 거리보다 크거나 같다면
	{
		Reverse = -1.0f; //방향 반전
	}
	else if (CurrentDistance <= 0.0f) //방향 전환후 원점으로 돌아왔다면
	{
		Reverse = 1.0f; //방향 반전
	}
}

