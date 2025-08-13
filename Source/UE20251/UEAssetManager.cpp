// Fill out your copyright notice in the Description page of Project Settings.


#include "UEAssetManager.h"

UUEAssetManager::UUEAssetManager()
{
}


UUEAssetManager& UUEAssetManager::Get()
{
	UUEAssetManager* Singleton = Cast<UUEAssetManager>(GEngine->AssetManager);

	return *Singleton;
}

void UUEAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UE_LOG(LogUE20251, Warning, TEXT("AssetManager StartInitialLoading"));

	// 초기 로딩 시 필요한 리소스를 미리 로딩한다.
}

void UUEAssetManager::FinishInitialLoading()
{
	Super::FinishInitialLoading();
}

UDataTable* UUEAssetManager::FindDataTable(const FName& TableName) const
{
	// 프로젝트 세팅에서 지정한 이름으로 얻어온다.
	FPrimaryAssetType AssetType = FPrimaryAssetType(TEXT("DataTable"));

	// 얻어온 PrimaryAssetType을 이용해서 PrimaryAssetId 배열을 얻어온다.
	TArray<FPrimaryAssetId> AssetIds;
	GetPrimaryAssetIdList(AssetType, AssetIds);

	// 위에서 얻어온 배열을 반복하며 원하는 데이터 테이블을 찾는다.
	for (auto& AssetId : AssetIds)
	{
		// Asset 이름을 얻어온다.
		FString AssetName = AssetId.PrimaryAssetName.ToString();

		if (AssetName == TableName.ToString())
		{
			FAssetData AssetData;

			// AssetId를 이용해서 AssetData를 얻어온다.
			GetPrimaryAssetData(AssetId, AssetData);

			UDataTable* Table = Cast<UDataTable>(AssetData.GetAsset());

			if (Table)
				return Table;

			else
			{
				// 로딩을 해서 반환한다.
				Table = Cast<UDataTable>(GetPrimaryAssetObject(AssetId));

				return Table;
			}
		}
	}

	return nullptr;
}
