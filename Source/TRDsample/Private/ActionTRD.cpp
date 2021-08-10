// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTRD.h"

FAsyncTask<TRDAbandonableTaskTest>* Tasker_01; // define thread variable 


// Sets default values for this component's properties
UActionTRD::UActionTRD(){
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActionTRD::BeginPlay(){
	Super::BeginPlay();
}


// Called every frame
void UActionTRD::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UActionTRD::SetupItems(int max, float range, FVector shiftLoc, int seg ) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UActionTRD::makeArray(){
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		items.Emplace(nullptr);
	}
}

void UActionTRD::calibrateEmplace(FVector shiftLoc){
	int segmentCounter = 1;
	for (int i = 0; i < arrEmplace.Num(); i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}

}


void UActionTRD::checkTarget(FVector targetLocation, float range){		
	(new FAutoDeleteAsyncTask<TRDAbandonableTaskTest>(range, targetLocation, maxArrayItems, arrEmplace, items, od))->StartBackgroundTask();	
}

void UActionTRD::ActivateItems(int index, bool b) {
	const FString cmd = FString::Printf(TEXT("SetColor %s"), b ? TEXT("true") : TEXT("false"));
	if (items[index]) items[index]->CallFunctionByNameWithArguments(*cmd, od, NULL, true);
}

TArray<FVector> UActionTRD::getLocations() {
	return arrEmplace;
}


void UActionTRD::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}


///////////////////////////////////

//  ----------- // destroy thread

void UActionTRD::DestroyThread(){
	if (Tasker_01){
		Tasker_01->EnsureCompletion();
		delete Tasker_01;
		Tasker_01 = NULL;
	}
}





