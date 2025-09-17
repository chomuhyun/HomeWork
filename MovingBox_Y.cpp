#include "MovingBox_Y.h"
#include "TimerManager.h"

AMovingBox_Y::AMovingBox_Y()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	YSpeed = 90.0f;
	FwdSpeed = 90.0f;
}

void AMovingBox_Y::BeginPlay()
{
	Super::BeginPlay();

	//시작 되자 마자 타이머 실행 5초뒤 이동
	GetWorld()->GetTimerManager().SetTimer(
		StartTimer,
		this,
		&AMovingBox_Y::StartForwardMove,
		5.0f,
		false
	);
}

void AMovingBox_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Upvector = GetActorUpVector(); //방향 위아래로 

	if (FMath::IsNearlyZero(YSpeed)) return;

	float MovingTotal = YSpeed * DeltaTime * Reverse; // 현재 속도에서 리버스 변수 곱해서 방향 설정

	AddActorLocalOffset(Upvector * MovingTotal); // 설정한 방향으로 이동

	CurrentDistance += MovingTotal; // 이동한 거리 계산

	if (CurrentDistance >= MaxDistance) //만약 현재 이동거리가 목표 거리보다 크거나 같다면
	{
		Reverse = -1.0f; //방향 반전
	}
	else if (CurrentDistance <= 0.0f) //방향 전환후 원점으로 돌아왔다면
	{
		Reverse = 1.0f; //방향 반전
	}

	if (MoveForWard && !FMath::IsNearlyZero(FwdSpeed)) // MoveForward bool값으로 이동 할지 말지를 판단
	{
		FVector Forward = GetActorForwardVector();
		float MoveFwd = FwdSpeed * DeltaTime * Reverse_Fwd;
		AddActorLocalOffset(Forward * MoveFwd);
		CurrentDistance_Fwd += MoveFwd;

		if (CurrentDistance_Fwd >= MaxDistance)
		{
			Reverse_Fwd = -1.0f;
		}
		else if (CurrentDistance_Fwd <= 0.0f)
		{
			Reverse_Fwd = 1.0f;
		}
	}
}

void AMovingBox_Y::StartForwardMove()
{
	MoveForWard = true;

	// 5초 후 정지 상태로 전환
	GetWorld()->GetTimerManager().SetTimer(
		StopTimer,
		this,
		&AMovingBox_Y::StopForwardMove,
		5.0f,
		false
	);
}

void AMovingBox_Y::StopForwardMove()
{
	MoveForWard = false;

	// 3.5초 후 다시 이동 시작
	GetWorld()->GetTimerManager().SetTimer(
		StartTimer,
		this,
		&AMovingBox_Y::StartForwardMove,
		3.5f,
		false 
	);
}