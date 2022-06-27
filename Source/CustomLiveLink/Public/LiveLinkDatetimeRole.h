// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LiveLinkTypes.h"
#include "Roles/LiveLinkBasicRole.h"
#include "LiveLinkDatetimeRole.generated.h"

UENUM(BlueprintType)
enum EDay
{
	Monday UMETA(DisplayName = "MON"),
	Tuesday UMETA(DisplayName = "TUE"),
	Wednesday UMETA(DisplayName = "WED"),
	Thursday UMETA(DisplayName = "THU"),
	Friday UMETA(DisplayName = "FRI"),
	Saturday UMETA(DisplayName = "SAT"),
	Sunday UMETA(DisplayName = "SUN")
};

UENUM(BlueprintType)
enum EMonth
{
	NoneMonth = 0 UMETA(DisplayName = "NONE"),
	January UMETA(DisplayName = "JAN"),
	February UMETA(DisplayName = "FEB"),
	March UMETA(DisplayName = "MAR"),
	April UMETA(DisplayName = "APR"),
	May UMETA(DisplayName = "MAY"),
	June UMETA(DisplayName = "JUN"),
	July UMETA(DisplayName = "JUL"),
	August UMETA(DisplayName = "AUG"),
	September UMETA(DisplayName = "SEP"),
	October UMETA(DisplayName = "OCT"),
	November UMETA(DisplayName = "NOV"),
	December UMETA(DisplayName = "DEC")
};

USTRUCT(BlueprintType)
struct FLiveLinkDatetimeStaticData : public FLiveLinkBaseStaticData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Data")
	bool bHasDatetime = true;
};

USTRUCT(BlueprintType)
struct FLiveLinkDatetimeFrameData : public FLiveLinkBaseFrameData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Hours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	TEnumAsByte<EDay> WeekDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Data")
	int32 Year;
};

USTRUCT(BlueprintType)
struct FliveLinkDatetimeBlueprintData : public FLiveLinkBaseBlueprintData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Data")
	FLiveLinkDatetimeStaticData StaticData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Data")
	FLiveLinkDatetimeFrameData FrameData;
};

/**
 * 
 */
UCLASS()
class CUSTOMLIVELINK_API ULiveLinkDatetimeRole : public ULiveLinkBasicRole
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetStaticDataStruct() const override;
	virtual UScriptStruct* GetFrameDataStruct() const override;
	virtual UScriptStruct* GetBlueprintDataStruct() const override;
	virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;
	virtual FText GetDisplayName() const override;
};
