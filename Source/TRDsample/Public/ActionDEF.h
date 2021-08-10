// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/OutputDeviceNULL.h"
#include "ActionDEF.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRDSAMPLE_API UActionDEF : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionDEF();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int maxArrayItems = 12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int areaRange = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int areaSegment = 2;

	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void SetupItems(int max, float range, FVector shiftLoc, int seg = 2);

	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void checkTarget(FVector targetLocation = FVector::ZeroVector, float range = 1);

	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		TArray<FVector> getLocations();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		TArray<AActor*> items;

	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void setItems(int index, AActor* obj);


protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<FVector> arrEmplace;

private:
	void makeArray();
	void calibrateEmplace(FVector shiftLoc = FVector::ZeroVector);
	FOutputDeviceNull od;

};