#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBox.generated.h"

UCLASS()
class MOVINGOBJECT_API AMovingBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingBox();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float FwdSpeed; // 이동 속력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float MaxDistance = 300.0f; //목표 거리

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box|Properties")
	float CurrentDistance = 0.0f; // 이동 거리 측정
	float Reverse = 1.0f; // 방향 반전
};
