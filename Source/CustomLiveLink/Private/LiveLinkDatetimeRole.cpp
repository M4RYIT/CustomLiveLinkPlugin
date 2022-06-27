// Fill out your copyright notice in the Description page of Project Settings.


#include "LiveLinkDatetimeRole.h"

UScriptStruct* ULiveLinkDatetimeRole::GetStaticDataStruct() const
{
    return FLiveLinkDatetimeStaticData::StaticStruct();
}

UScriptStruct* ULiveLinkDatetimeRole::GetFrameDataStruct() const
{
    return FLiveLinkDatetimeFrameData::StaticStruct();
}

UScriptStruct* ULiveLinkDatetimeRole::GetBlueprintDataStruct() const
{
    return FliveLinkDatetimeBlueprintData::StaticStruct();
}

bool ULiveLinkDatetimeRole::InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const
{
    FliveLinkDatetimeBlueprintData* BlueprintData = OutBlueprintData.Cast<FliveLinkDatetimeBlueprintData>();
    const FLiveLinkDatetimeStaticData* StaticData = InSourceData.StaticData.Cast<FLiveLinkDatetimeStaticData>();
    const FLiveLinkDatetimeFrameData* FrameData = InSourceData.FrameData.Cast<FLiveLinkDatetimeFrameData>();

    if (BlueprintData && StaticData && FrameData)
    {
        GetStaticDataStruct()->CopyScriptStruct(&BlueprintData->StaticData, StaticData);
        GetFrameDataStruct()->CopyScriptStruct(&BlueprintData->FrameData, FrameData);
        return true;
    }

    return false;
}

FText ULiveLinkDatetimeRole::GetDisplayName() const
{
    return FText::FromString("Datetime");
}
