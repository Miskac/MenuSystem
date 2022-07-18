// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"

// Declaring our own custom delegates for the menu class to bind callbacks to

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMultiplayerSessionsSubsystem();

	// To handle session funcionality the menu will call these

	void CreateSession(int32 NumPublicConnections, FString MatchType);

	void FindSessions(int32 MaxSearchResults);

	void JoinSession(FOnlineSessionSearchResult& SearchResult);

	void DestroySession();
	void StartSession();

	// Our own custom delegates for the menu class to bind callbacks to

	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;

protected:

	// Internal callbacks for the delegates well add to the online session interface delage list
	// These dont need to be called outside of this class

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	// To add to the online session interface delagate list
	// We'll bind our multiplayer sessions subsystem internal callbacks to these

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;

	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FDelegateHandle FindSessionsCompleteDelegateHandle;

	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FDelegateHandle StartSessionCompleteDelegateHandle;

	bool bCreateSessionOnDestroy{false};

	int32 LastNumPublicConnections;

	FString LastMatchType;

};
