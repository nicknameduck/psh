// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingGameMode.h"
#include "Blueprint/UserWidget.h"

ALoadingGameMode::ALoadingGameMode()
{
	DefaultPawnClass = nullptr;
	HUDClass = nullptr;
}

void ALoadingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ALoadingGameMode::InitGameState()
{
	Super::InitGameState();
}

void ALoadingGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* ALoadingGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* PlayerCtrl = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	// 옵션 스트링에 전달된 데이터를 얻어온다.
	// Job=%d MapName=Main MapPath=/Game/Maps/Main PlayerName=%s
	FParse::Value(*Options, TEXT("Job="), mJob);
	FParse::Value(*Options, TEXT("MapName="), mMapName);
	FParse::Value(*Options, TEXT("MapPath="), mMapPath);
	FParse::Value(*Options, TEXT("PlayerName="), mPlayerName);

	// 다음 레벨을 백그라운드에서 비동기로 로딩한다.
	// 1번인자 : 레벨 경로가 들어간다.
	// 2번인자 : 레벨 로딩 완료시 호출될 함수를 등록한다.
	// 3번인자 : 로딩 우선순위.
	// 4번인자 : EPackageFlags 가 들어간다.
	/*
	PKG_ContainsMap : 레벨 데이터를 포함하고 있음을 의미.
	PKG_CompiledIn : 코드에 의해 고정으로 포함된 패키지(UCLASS가 들어있는 패키지)
	PKG_EditorOnly : 에디터 전용.(게임에서는 사용불가)
	*/
	LoadPackageAsync(mMapPath, FLoadPackageAsyncDelegate::CreateUObject(this, &ALoadingGameMode::LoadingAsyncComplete), 0, PKG_ContainsMap);

	return PlayerCtrl;
}

void ALoadingGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ALoadingGameMode::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UUserWidget>	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Loading/UI_Loading.UI_Loading_C'"));

	if (IsValid(WidgetClass))
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);

		if (IsValid(Widget))
		{
			Widget->AddToViewport();
		}
	}
}

void ALoadingGameMode::LoadingAsyncComplete(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
{
	if (Result == EAsyncLoadingResult::Succeeded)
	{
		FString	OptionString = FString::Printf(TEXT("Job=%d PlayerName=%s "), mJob, *mPlayerName);

		UGameplayStatics::OpenLevel(GetWorld(), *mMapName, true, OptionString);
	}
}
