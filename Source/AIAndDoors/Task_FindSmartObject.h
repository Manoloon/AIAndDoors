// Copyright Pablo Rodrigo Sanchez, Inc. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "Task_FindSmartObject.generated.h"

class UGameplayBehavior;
class USmartObjectComponent;
class USmartObjectDefinition;

UCLASS()
class AIANDDOORS_API UTask_FindSmartObject : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USmartObjectDefinition> SmartObjectDefinition;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SOClaimedBBSelector;
};
