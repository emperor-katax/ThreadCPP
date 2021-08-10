// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/QueuedThreadPool.h"
#include "Misc/OutputDeviceNULL.h"
#include "Async/AsyncWork.h"
#include "Math/UnrealMathUtility.h"
#include "ActionTRD.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRDSAMPLE_API UActionTRD : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UActionTRD();

	// destroy test thread
	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void DestroyThread();	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int maxArrayItems = 12;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int areaRange = 3;		
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActionTRD Functions")
		int areaSegment = 2;	
	
	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void SetupItems(int max, float range, FVector shiftLoc, int seg = 2);

	UFUNCTION(BlueprintCallable, Category = "ActionTRD Functions")
		void checkTarget(FVector targetLocation = FVector::ZeroVector, float range = 64);
	
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
	void ActivateItems(int index, bool b);
	void calibrateEmplace(FVector shiftLoc = FVector::ZeroVector);	
	bool active = false;
	float temp_range = 64.f;
	FVector temp_targetLocation = FVector::OneVector;
	FOutputDeviceNull od;
	float temp_01 = 0;

};


////////////////////////////////////////////////////
////////////////////////////////////////////////////


class TRDAbandonableTaskTest : public FNonAbandonableTask 
{
	
	// TRDAbandonableTaskTest is custom name
	// FNonAbandonableTask is belong to engine 
	// class variables
	float range;
	FVector targetLocation;
	int max;	
	TArray<FVector> arrEmp;
	TArray<AActor*> itms;
	FOutputDeviceNull od;

public:
	//Default constructor.
	TRDAbandonableTaskTest(
		float rng,  
		FVector loc, 
		int mx, 
		TArray<FVector> emp, 
		TArray<AActor*> itm, 
		FOutputDeviceNull odn) // set input parameters of class
	{
		// set variable(s) to be used as "parameter" of thread
		this->range = rng;
		this->targetLocation = loc;
		this->max = mx; // maxArrayItems
		this->arrEmp = emp;// arrEmplace
		this->itms = itm; // items
		this->od = odn; //FOutputDeviceNull od;

	}

	// Default destructor
	~TRDAbandonableTaskTest() {
		//UE_LOG(LogTemp, Warning, TEXT("Task Deleted"));	
	}

	//This function is needed from the API of the engine. So always add this.
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(TRDAbandonableTaskTest, STATGROUP_ThreadPoolAsyncTasks);
	}

	//This function is called when we tell our task to execute... codes here is handle by a new thread
	void DoWork()
	{
		for (int i = 0; i < max; i++) {
			const FString cmd = FString::Printf(TEXT("SetColor %s"), (FVector::Dist(arrEmp[i], targetLocation) < range) ? TEXT("true") : TEXT("false"));
			if (itms[i]) itms[i]->CallFunctionByNameWithArguments(*cmd, od, NULL, true);
		}
	}
};



// https://unrealcpp.com/debug-logging/  --  UE_LOG
// ----------------------------------------  TArray
// https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/TArrays/index.html
// https://michaeljcole.github.io/wiki.unrealengine.com/Dynamic_Arrays_in_UE4_C++/
// https://www.codegrepper.com/code-examples/cpp/ue4+c%2B%2B+array
// 
// https://stackoverflow.com/questions/54812276/ue4-c-adding-an-object-with-a-tarray-member-by-value-to-a-tarray-causes
// https://www.programmersought.com/article/7177121689/


