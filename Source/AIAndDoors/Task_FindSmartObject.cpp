// Copyright Pablo Rodrigo Sanchez, Inc. All Rights Reserved.

#include "Task_FindSmartObject.h"
#include "GameFramework/Character.h"
#include "BlackboardKeyType_SOClaimHandle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SmartObjectSubsystem.h"

EBTNodeResult::Type
UTask_FindSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	if (!IsValid(GetWorld()))
	{
		return EBTNodeResult::Failed;
	}
	USmartObjectSubsystem* SOSubSystem = GetWorld()->GetSubsystem<USmartObjectSubsystem>();
	AAIController* MyController = OwnerComp.GetAIOwner();
	ACharacter* Character = Cast<ACharacter>(MyController->GetPawn());
	if (!IsValid(SOSubSystem) || !IsValid(MyController) || !IsValid(Character))
	{
		return EBTNodeResult::Failed;
	}
	 //Cast<AAIController>(OwnerComp.GetOwner());
	
	const FVector MinZone = Character->GetActorLocation() - FVector{ 2000 };
	const FVector MaxZone = Character->GetActorLocation() + FVector{ 2000 };
	FBox Zone{ MinZone, MaxZone };
	FSmartObjectRequest Request;
	Request.QueryBox = Request.QueryBox.ShiftBy(Character->GetActorLocation() + MaxZone);

	Request.Filter.BehaviorDefinitionClasses.Emplace(SmartObjectDefinition);

	TArray<FSmartObjectRequestResult> RequestResults;

	SOSubSystem->FindSmartObjects(Request, RequestResults);
	if (RequestResults.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	FSmartObjectRequestResult ResultItem = RequestResults.Top();
	FConstStructView UserData = {};
	FSmartObjectClaimHandle Result = SOSubSystem->MarkSlotAsClaimed(ResultItem.SlotHandle, ESmartObjectClaimPriority::High, UserData);
	UBlackboardComponent* BlackBoardComp = MyController->GetBlackboardComponent();
	if(!IsValid(BlackBoardComp))
	{
		return EBTNodeResult::Failed;
	}
	BlackBoardComp->SetValue<UBlackboardKeyType_SOClaimHandle>(SOClaimedBBSelector.SelectedKeyName, Result);
	return EBTNodeResult::Succeeded;
}