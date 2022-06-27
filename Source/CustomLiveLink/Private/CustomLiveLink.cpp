// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomLiveLink.h"

#define LOCTEXT_NAMESPACE "FCustomLiveLinkModule"

void FCustomLiveLinkModule::StartupModule()
{
}

void FCustomLiveLinkModule::ShutdownModule()
{
}

FCustomLiveLinkSource::FCustomLiveLinkSource() : Client(nullptr), Socket(nullptr)
{
}

bool FCustomLiveLinkSource::IsSourceStillValid() const
{
	return true;
}

bool FCustomLiveLinkSource::RequestSourceShutdown()
{
	Client = nullptr;
	if (Socket) Socket->Close();
	return true;
}

FText FCustomLiveLinkSource::GetSourceType() const
{
	return FText::FromString("Custom LiveLink Source");
}

FText FCustomLiveLinkSource::GetSourceMachineName() const
{
	return FText::FromString(FPlatformProcess::ComputerName());
}

FText FCustomLiveLinkSource::GetSourceStatus() const
{
	return FText::FromString("Active");
}

TStatId FCustomLiveLinkSource::GetStatId() const
{
	return TStatId();
}

bool FCustomLiveLinkSource::IsTickableInEditor() const
{
	return false;
}

void FCustomLiveLinkSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
	if (Socket) Socket->Close();

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	TSharedPtr<FInternetAddr> EndpointInternetAddr = SocketSubsystem->CreateInternetAddr();
	bool bIsIpValid = false;
	EndpointInternetAddr->SetIp(TEXT("127.0.0.1"), bIsIpValid);
	EndpointInternetAddr->SetPort(12345);

	FIPv4Endpoint Endpoint = FIPv4Endpoint(EndpointInternetAddr);

	Socket = FUdpSocketBuilder(TEXT("AIV UDP Server"))
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint);

	Client = InClient;

	DatetimeSubject.SubjectName = FLiveLinkSubjectName(TEXT("Datetime Subject"));
	DatetimeSubject.Source = InSourceGuid;

	FLiveLinkStaticDataStruct DatetimeStaticData;
	DatetimeStaticData.InitializeWith(FLiveLinkDatetimeStaticData::StaticStruct(), nullptr);
	DatetimeStaticData.Cast<FLiveLinkDatetimeStaticData>()->bHasDatetime = true;

	Client->PushSubjectStaticData_AnyThread(DatetimeSubject, ULiveLinkDatetimeRole::StaticClass(), MoveTemp(DatetimeStaticData));
}

void FCustomLiveLinkSource::Tick(float DeltaTime)
{
	if (Client)
	{
		if (Socket)
		{
			uint32 RequiredDataSize;
			if (!Socket->HasPendingData(RequiredDataSize))
			{
				ClearFrames();
				return;
			}

			TArray<uint8> Data;
			Data.AddUninitialized(RequiredDataSize);
			int32 ReceivedDataSize;
			if (!Socket->Recv(Data.GetData(), Data.Num(), ReceivedDataSize))
			{
				ClearFrames();
				return;
			}

			// not enough data?
			if (ReceivedDataSize < (sizeof(uint32) * 7)) return;

			uint32* Values = reinterpret_cast<uint32*>(Data.GetData());
			FLiveLinkFrameDataStruct FrameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkDatetimeFrameData::StaticStruct());
			FLiveLinkDatetimeFrameData* FrameData = FrameDataStruct.Cast<FLiveLinkDatetimeFrameData>();
			FrameData->WorldTime = FPlatformTime::Seconds();
			FrameData->Hours = Values[0];
			FrameData->Minutes = Values[1];
			FrameData->Seconds = Values[2];
			FrameData->WeekDay = (EDay)Values[3];
			FrameData->Day = Values[4];
			FrameData->Month = Values[5];
			FrameData->Year = Values[6];

			Client->PushSubjectFrameData_AnyThread(DatetimeSubject, MoveTemp(FrameDataStruct));
			return;
		}

		ClearFrames();
	}
}

void FCustomLiveLinkSource::ClearFrames()
{
	Client->ClearAllSubjectsFrames_AnyThread();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomLiveLinkModule, CustomLiveLink)


