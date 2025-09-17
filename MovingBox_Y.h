#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBox_Y.generated.h"

UCLASS()
class MOVINGOBJECT_API AMovingBox_Y : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMovingBox_Y(); 

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float YSpeed; // �̵� �ӷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float FwdSpeed; // �̵� �ӷ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float MaxDistance = 300.0f; //��ǥ �Ÿ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float CurrentDistance = 0.0f; // �̵� �Ÿ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float CurrentDistance_Fwd = 0.0f; // �̵� �Ÿ� ����
	
	float Reverse = 1.0f; // ���� ����
	float Reverse_Fwd = 1.0f;
	FTimerHandle StartTimer;
	FTimerHandle StopTimer;

	void StartForwardMove();
	void StopForwardMove();

	bool MoveForWard = false;
};
