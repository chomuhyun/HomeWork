#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockRotation.generated.h"

UCLASS()
class MOVINGOBJECT_API ABlockRotation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockRotation();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block|Properties")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
