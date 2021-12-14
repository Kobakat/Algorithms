#include "IKSolver.h"
#include "VisualIK.h"

AIKSolver::AIKSolver()
{
	PrimaryActorTick.bCanEverTick = true;
	ChainSegments = 2;
	ChainSegmentLength = 200;
	ChainLength = 400;
	SolverIterations = 10;
}

void AIKSolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Effector != nullptr && IKChain != nullptr)
	{
		Solve();
	}
}

void AIKSolver::Solve()
{
	const float ChainLengthSq = ChainLength * ChainLength;
	const float EffectorDistanceSq = (Effector->GetActorLocation() - IKChain->GetActorLocation()).SizeSquared();

	//Current chain length is beyond maximum extent of the arm so just straighten in the direction of the effector
	if (EffectorDistanceSq >= ChainLengthSq - KINDA_SMALL_NUMBER)
	{
		const FVector NormalizedDirection = (Effector->GetActorLocation() - IKChain->GetActorLocation()).GetSafeNormal();
		
		//For now we are only using 2 bone IK		
		IKChain->MiddleBone()->SetRelativeLocation(NormalizedDirection * ChainSegmentLength);
		IKChain->EndBone()->SetRelativeLocation(NormalizedDirection * ChainSegmentLength);
	}

	//Effector lies within the reachable extent of the arm so we begin FABRIK
	else
	{
		for (int i = 0; i < SolverIterations; i++)
		{
			//Moving back

			IKChain->EndBone()->SetWorldLocation(Effector->GetActorLocation());

			const FVector Offset = IKChain->EndBone()->GetComponentLocation() +
				(IKChain->MiddleBone()->GetComponentLocation() - IKChain->EndBone()->GetComponentLocation()).GetSafeNormal() *
				ChainSegmentLength;

			IKChain->MiddleBone()->SetWorldLocation(Offset);


			//Moving Forward

			const FVector MiddleOffset = IKChain->BaseBone()->GetComponentLocation() +
				(IKChain->MiddleBone()->GetComponentLocation() - IKChain->BaseBone()->GetComponentLocation()).GetSafeNormal() *
				ChainSegmentLength;

			const FVector EndOffset = IKChain->MiddleBone()->GetComponentLocation() +
				(IKChain->EndBone()->GetComponentLocation() - IKChain->MiddleBone()->GetComponentLocation()).GetSafeNormal() *
				ChainSegmentLength;

			IKChain->MiddleBone()->SetWorldLocation(MiddleOffset);
			IKChain->EndBone()->SetWorldLocation(EndOffset);

			//The end bone is almost at the effector so we consider this complete
			if ((IKChain->EndBone()->GetComponentLocation() - Effector->GetActorLocation()).IsNearlyZero())
			{
				break;
			}
		}
	}
}
