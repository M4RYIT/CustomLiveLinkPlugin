// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "ILiveLinkSource.h"
#include "ILiveLinkClient.h"
#include "SocketSubsystem.h"
#include "LiveLinkDatetimeRole.h"
#include "Common/UdpSocketBuilder.h"

class CUSTOMLIVELINK_API FCustomLiveLinkSource : public ILiveLinkSource, public FTickableGameObject
{
public:
	FCustomLiveLinkSource();

	bool IsSourceStillValid() const override;
	bool RequestSourceShutdown() override;
	FText GetSourceType() const override;
	FText GetSourceMachineName() const override;
	FText GetSourceStatus() const override;
	TStatId GetStatId() const override;
	bool IsTickableInEditor() const override;
	void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;
	void Tick(float DeltaTime) override;
	void ClearFrames();

	FLiveLinkSubjectKey DatetimeSubject;
	ILiveLinkClient* Client;
	FSocket* Socket;
};

class FCustomLiveLinkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
