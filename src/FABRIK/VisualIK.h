#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisualIK.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class IKTEST_API AVisualIK : public AActor
{
	GENERATED_BODY()
	
public:	
	AVisualIK();

	bool ShouldTickIfViewportsOnly() const override { return true; }

	void Tick(float DeltaSeconds);

	FORCEINLINE USceneComponent* BaseBone() const { return Base; }

	FORCEINLINE USceneComponent* MiddleBone() const { return Middle; }

	FORCEINLINE USceneComponent* EndBone() const { return End; }

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Middle;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* End;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere)
	USplineMeshComponent* BaseToMiddle;

	UPROPERTY(VisibleAnywhere)
	USplineMeshComponent* MiddleToEnd;
};
