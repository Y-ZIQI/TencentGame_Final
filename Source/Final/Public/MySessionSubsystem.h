// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "MySessionSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FMySession
{
	GENERATED_BODY()

public:

	//TSharedPtr<FOnlineSessionSearch> SessionSearch;
	//TSharedPtr<FOnlineSessionSearchResult> SessionResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySession")
		FString SessionName;

	UPROPERTY(BlueprintReadOnly, Category = "MySession")
		int32 idx;

	UPROPERTY(BlueprintReadOnly, Category = "MySession")
		int32 pingInMs;

	UPROPERTY(BlueprintReadOnly, Category = "MySession")
		FString owningUserName;

	UPROPERTY(BlueprintReadOnly, Category = "MySession")
		int32 numOpenPrivateConnections;

	UPROPERTY(BlueprintReadOnly, Category = "MySession")
		int32 numOpenPublicConnections;

	TSharedPtr<FOnlineSessionSearch> SessionSearchPtr;

	FMySession()
	{
	}
	FMySession(FString Name) 
	{
		SessionName = Name;
	}
	/*
	FOnlineSessionSearchResult& getSessionSearchResult()
	{
		return SessionSearchPtr->SearchResults[idx];
	}
	UFUNCTION(BlueprintCallable, Category = "MySession")
	int32 getPingInMs()
	{
		return getSessionSearchResult().PingInMs;
	}
	UFUNCTION(BlueprintCallable, Category = "MySession")
	FString getOwningUserName()
	{
		return getSessionSearchResult().Session.OwningUserName;
	}
	UFUNCTION(BlueprintCallable, Category = "MySession")
	int32 getNumOpenPrivateConnections()
	{
		return getSessionSearchResult().Session.NumOpenPrivateConnections;
	}
	UFUNCTION(BlueprintCallable, Category = "MySession")
	int32 getNumOpenPublicConnections()
	{
		return getSessionSearchResult().Session.NumOpenPublicConnections;
	}
	*/
};

struct RoomInfo 
{
	FString RoomName;
	FString RoomPassword;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnCreateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnStartSessionComplete, bool, Successful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FCSOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful);
DECLARE_MULTICAST_DELEGATE_OneParam(FCSOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnDestroySessionComplete, bool, Successful);


/**
 * 
 */
UCLASS(BlueprintType)
class FINAL_API UMySessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMySessionSubsystem();
	
	UFUNCTION(BlueprintCallable, Category = "MySessionSubsystem")
	void CreateSession(int32 NumPublicConnections, bool IsLANMatch);
	FCSOnCreateSessionComplete OnCreateSessionCompleteEvent;
	FCSOnStartSessionComplete OnStartSessionCompleteEvent;

	UFUNCTION(BlueprintCallable, Category = "MySessionSubsystem")
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);
	FCSOnFindSessionsComplete OnFindSessionsCompleteEvent;

	UFUNCTION(BlueprintCallable, Category = "MySessionSubsystem")
	void JoinSession(const FString& SessionName);
	void JoinGameSession(const FOnlineSessionSearchResult& SessionResult);
	FCSOnJoinSessionComplete OnJoinGameSessionCompleteEvent;

	UFUNCTION(BlueprintCallable, Category = "MySessionSubsystem")
	void DestroySession();
	FCSOnDestroySessionComplete OnDestroySessionCompleteEvent;

protected:
	void OnCreateSessionCompleted(FName SessionName, bool Successful);
	void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsCompleted(bool Successful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleted(FName SessionName, bool Successful);

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate; 
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

public:
	UPROPERTY(BlueprintReadOnly, Category = "MySession")
	TArray<FMySession> FMySessions;
	TMap<int32, RoomInfo> UserRoomInfo;
};
