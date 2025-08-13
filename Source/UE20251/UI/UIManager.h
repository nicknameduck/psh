// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UIInfo.h"

class UE20251_API CUIManager
{
private:
	CUIManager();
	~CUIManager();

private:
	TMap<FName, TObjectPtr<class UBaseUserWidget>>	mWidgetMap;

public:
	void AddWidget(const FName& WidgetName, class UBaseUserWidget* Widget);
	void DeleteWidget(const FName& WidgetName);

	template <typename T>
	T* FindWidget(const FName& WidgetName)
	{
		if (!mWidgetMap.Contains(WidgetName))
			return nullptr;

		return Cast<T>(mWidgetMap.FindRef(WidgetName));
	}

private:
	static CUIManager* mInst;

public:
	static CUIManager* GetInst()
	{
		if (!mInst)
			mInst = new CUIManager;
		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};
