#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IKSolver.generated.h"

class AVisualIK;

UCLASS()
class IKTEST_API AIKSolver : public AActor
{
	GENERATED_BODY()
	
public:	
	AIKSolver();

	void Solve();

	bool ShouldTickIfViewportsOnly() const override { return true; }

protected:
	
	UPROPERTY(EditAnywhere, Category = IK)
	AActor* Effector;

	UPROPERTY(EditAnywhere, Category = IK)
	AVisualIK* IKChain;

private:

	int32 SolverIterations;

	float ChainSegments;
	float ChainSegmentLength;
	float ChainLength;

public:	

	virtual void Tick(float DeltaTime) override;

};
