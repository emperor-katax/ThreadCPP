// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionDEF.h"

// Sets default values for this component's properties
UActionDEF::UActionDEF()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UActionDEF::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UActionDEF::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActionDEF::SetupItems(int max, float range, FVector shiftLoc, int seg) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UActionDEF::makeArray() {
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		items.Emplace(nullptr);
	}
}

void UActionDEF::calibrateEmplace(FVector shiftLoc) {
	int segmentCounter = 1;
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}
}


void UActionDEF::checkTarget(FVector targetLocation, float range) {
	for (int i = 0; i < maxArrayItems; i++) {
		const FString cmd = FString::Printf(TEXT("SetColor %s"), ((FVector::Dist(arrEmplace[i], targetLocation)) < range) ? TEXT("true") : TEXT("false"));
		items[i]->CallFunctionByNameWithArguments(*cmd, od, NULL, true);
	}

}

TArray<FVector> UActionDEF::getLocations() {
	return arrEmplace;
}


void UActionDEF::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}

