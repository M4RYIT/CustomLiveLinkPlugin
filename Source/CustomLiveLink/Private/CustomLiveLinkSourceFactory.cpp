// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLiveLinkSourceFactory.h"

FText UCustomLiveLinkSourceFactory::GetSourceDisplayName() const
{
    return FText::FromString("Custom LiveLink Source");
}

FText UCustomLiveLinkSourceFactory::GetSourceTooltip() const
{
    return FText::FromString("Custom LiveLink Tooltip");
}

TSharedPtr<ILiveLinkSource> UCustomLiveLinkSourceFactory::CreateSource(const FString& ConnectionString) const
{
    return MakeShared<FCustomLiveLinkSource>();
}
