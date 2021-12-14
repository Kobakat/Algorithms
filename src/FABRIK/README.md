Implementation of Forwards and Backward Reaching Inverse Kinematics in Unreal Engine 4 C++

Based on [this](http://andreasaristidou.com/publications/papers/FABRIK.pdf) wonderful and intuitive publication.

# Inverse Kinematics

Inverse Kinematics are a mathematical computation that generates the ever changing positional data for every joint in a chain. The two most practical uses for this are in 3D Animations, and Robotics. While Inverse kinematics can be used to generates positional data for a chain of any length, this implementation focuses on a two joint system. The best way to visualize this your arm where your shoulder remains in place. Your shoulder rotates and your elbow bends to ultimately move your hand to a desired location in the most efficent relative path possible (a straight line).

## Implementation

As mentioned above, this implementation is based on the FABRIK solver. This works by adjusting back and forth until a reasonably exact joint hierarchy is found, or by a capped iteration count. To aid in visualization, I'm also using my go to 3D Engine, Unreal, to do the heavy lifting on the graphical side. One more slight benefit to using unreal is the innate ability to parent object transforms which handles relative positioning for us.

To start, every Tick we are going to call the Solve method on an IKSolver object.

Our first step is to evaluate if we should actually use FABRIK or just extend our virtual arm to the closest we can get to our target location

```cpp
const float ChainLengthSq = ChainLength * ChainLength;
const float EffectorDistanceSq = (Effector->GetActorLocation() - IKChain->GetActorLocation()).SizeSquared();

//Current chain length is beyond maximum extent of the arm so just straighten in the direction of the effector
if (EffectorDistanceSq >= ChainLengthSq - KINDA_SMALL_NUMBER)
{
	const FVector NormalizedDirection = (Effector->GetActorLocation() - IKChain->GetActorLocation()).GetSafeNormal();
		
	IKChain->MiddleBone()->SetRelativeLocation(NormalizedDirection * ChainSegmentLength);
  IKChain->EndBone()->SetRelativeLocation(NormalizedDirection * ChainSegmentLength);
}
```

All this snippet does is check if the effector location is beyond the maximum extent of our arm. If it is, just stretch straight out in that direction! An optimization I'm using is to calculate square values of vectors because regular lengths require a square root computation which are expensive!

Otherwise, our effector is within are arms maximum reach though, lets start FABRIK.

First we place our hand at the exact target location before moving the elbow back to compensate

```cpp
//Moving back
IKChain->EndBone()->SetWorldLocation(Effector->GetActorLocation());

const FVector Offset = IKChain->EndBone()->GetComponentLocation() +
  (IKChain->MiddleBone()->GetComponentLocation() - IKChain->EndBone()->GetComponentLocation()).GetSafeNormal() *
  ChainSegmentLength;

IKChain->MiddleBone()->SetWorldLocation(Offset);
```

Next, we reposition the hand and elbow after taking into account our backwards displacement, now we shift forward

```cpp
//Moving Forward
const FVector MiddleOffset = IKChain->BaseBone()->GetComponentLocation() +
  (IKChain->MiddleBone()->GetComponentLocation() - IKChain->BaseBone()->GetComponentLocation()).GetSafeNormal() *
  ChainSegmentLength;

 const FVector EndOffset = IKChain->MiddleBone()->GetComponentLocation() +
  (IKChain->EndBone()->GetComponentLocation() - IKChain->MiddleBone()->GetComponentLocation()).GetSafeNormal() *
  ChainSegmentLength;

IKChain->MiddleBone()->SetWorldLocation(MiddleOffset);
IKChain->EndBone()->SetWorldLocation(EndOffset);
```

Lastly, we just check if the hand reached the effector, if it did, we're done! Otherwise, loop for as many solver iterations as we're allowed

```cpp
//The end bone is almost at the effector so we consider this complete
if ((IKChain->EndBone()->GetComponentLocation() - Effector->GetActorLocation()).IsNearlyZero())
{
  break;
}
```

The result is an awesome looking arm that compensates joint locations

![gif](https://github.com/Kobakat/Algorithms/blob/master/imgdump/IKGif.gif)
