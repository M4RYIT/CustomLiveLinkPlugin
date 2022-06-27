// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LiveLinkSourceFactory.h"
#include "CustomLiveLink.h"
#include "CustomLiveLinkSourceFactory.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMLIVELINK_API UCustomLiveLinkSourceFactory : public ULiveLinkSourceFactory
{
	GENERATED_BODY()

public:
	virtual FText GetSourceDisplayName() const;
	virtual FText GetSourceTooltip() const;
	virtual EMenuType GetMenuType() const { return EMenuType::MenuEntry; }
	TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const;
};
