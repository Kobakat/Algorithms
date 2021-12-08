#include "VisualIK.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

AVisualIK::AVisualIK()
{
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shoulder"));
	Middle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elbow"));
	End = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	BaseToMiddle = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Mesh One"));
	MiddleToEnd = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Mesh Two"));

	SetRootComponent(Base);
	Spline->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Middle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	End->AttachToComponent(Middle, FAttachmentTransformRules::KeepRelativeTransform);

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> JointHelper = 
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere"));

	Base->SetStaticMesh(JointHelper.Get());
	Middle->SetStaticMesh(JointHelper.Get());
	End->SetStaticMesh(JointHelper.Get());

	Middle->SetRelativeLocation(FVector(200, 0, 0));
	End->SetRelativeLocation(FVector(200, 0, 0));

	Spline->AddSplinePoint(End->GetComponentLocation(), ESplineCoordinateSpace::World);

	Spline->SetSplinePointType(0, ESplinePointType::Linear);
	Spline->SetSplinePointType(1, ESplinePointType::Linear);
	Spline->SetSplinePointType(2, ESplinePointType::Linear);

	BaseToMiddle->SetForwardAxis(ESplineMeshAxis::Y);
	MiddleToEnd->SetForwardAxis(ESplineMeshAxis::Y);

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> LigamentHelper = 
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Engine/EngineMeshes/Cylinder"));

	BaseToMiddle->SetStaticMesh(LigamentHelper.Get());
	MiddleToEnd->SetStaticMesh(LigamentHelper.Get());
}

void AVisualIK::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Spline->SetWorldLocationAtSplinePoint(1, Middle->GetComponentLocation());
	Spline->SetWorldLocationAtSplinePoint(2, End->GetComponentLocation());

	BaseToMiddle->SetStartPosition(Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	BaseToMiddle->SetEndPosition(Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));
	MiddleToEnd->SetStartPosition(Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));
	MiddleToEnd->SetEndPosition(Spline->GetLocationAtSplinePoint(2, ESplineCoordinateSpace::World));
}