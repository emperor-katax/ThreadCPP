// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTRDv2.h"

FAsyncTask<TRDAbandonableTaskTest2>* Tasker_02; // define thread variable 

// Sets default values for this component's properties
UActionTRDv2::UActionTRDv2(){
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActionTRDv2::BeginPlay(){
	Super::BeginPlay();	
}


// Called every frame
void UActionTRDv2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UActionTRDv2::SetupItems(int max, float range, FVector shiftLoc, int seg) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UActionTRDv2::makeArray() {
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		items.Emplace(nullptr);
	}
}

void UActionTRDv2::calibrateEmplace(FVector shiftLoc) {
	int segmentCounter = 1;
	for (int i = 0; i < arrEmplace.Num(); i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}
}


void UActionTRDv2::checkTarget(FVector targetLocation, float range) {
	for (int i = 0; i < maxArrayItems; i++) {
		tempV = arrEmplace[i];
		tempA = items[i];
		(new FAutoDeleteAsyncTask<TRDAbandonableTaskTest2>(range, targetLocation, maxArrayItems, tempV, tempA, od))->StartBackgroundTask();
	}
}

void UActionTRDv2::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}

TArray<FVector> UActionTRDv2::getLocations() {
	return arrEmplace;
}


///////////////////////////////////

//  ----------- // destroy thread

void UActionTRDv2::DestroyThread(){
	if (Tasker_02){
		Tasker_02->EnsureCompletion();
		delete Tasker_02;
		Tasker_02 = NULL;
		active = true;
	}
}







