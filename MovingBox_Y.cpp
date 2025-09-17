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

	//���� ���� ���� Ÿ�̸� ���� 5�ʵ� �̵�
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

	FVector Upvector = GetActorUpVector(); //���� ���Ʒ��� 

	if (FMath::IsNearlyZero(YSpeed)) return;

	float MovingTotal = YSpeed * DeltaTime * Reverse; // ���� �ӵ����� ������ ���� ���ؼ� ���� ����

	AddActorLocalOffset(Upvector * MovingTotal); // ������ �������� �̵�

	CurrentDistance += MovingTotal; // �̵��� �Ÿ� ���

	if (CurrentDistance >= MaxDistance) //���� ���� �̵��Ÿ��� ��ǥ �Ÿ����� ũ�ų� ���ٸ�
	{
		Reverse = -1.0f; //���� ����
	}
	else if (CurrentDistance <= 0.0f) //���� ��ȯ�� �������� ���ƿԴٸ�
	{
		Reverse = 1.0f; //���� ����
	}

	if (MoveForWard && !FMath::IsNearlyZero(FwdSpeed)) // MoveForward bool������ �̵� ���� ������ �Ǵ�
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

	// 5�� �� ���� ���·� ��ȯ
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

	// 3.5�� �� �ٽ� �̵� ����
	GetWorld()->GetTimerManager().SetTimer(
		StartTimer,
		this,
		&AMovingBox_Y::StartForwardMove,
		3.5f,
		false 
	);
}