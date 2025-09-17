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

	float MovingTotal = FwdSpeed * DeltaTime * Reverse; // ���� �ӵ����� ������ ���� ���ؼ� ���� ����

	AddActorLocalOffset(Forward * MovingTotal); // ������ �������� �̵�

	CurrentDistance += MovingTotal; // �̵��� �Ÿ� ���

	if (CurrentDistance >= MaxDistance) //���� ���� �̵��Ÿ��� ��ǥ �Ÿ����� ũ�ų� ���ٸ�
	{
		Reverse = -1.0f; //���� ����
	}
	else if (CurrentDistance <= 0.0f) //���� ��ȯ�� �������� ���ƿԴٸ�
	{
		Reverse = 1.0f; //���� ����
	}
}

