// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "BaseUserWidget.h"

CUIManager* CUIManager::mInst = nullptr;

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::AddWidget(const FName& WidgetName, UBaseUserWidget* Widget)
{
	// 같은 이름으로 등록된 위젯이 있을 경우
	if (mWidgetMap.Contains(WidgetName))
		return;

	mWidgetMap.Add(WidgetName, Widget);
}

void CUIManager::DeleteWidget(const FName& WidgetName)
{
	if (!mWidgetMap.Contains(WidgetName))
		return;

	mWidgetMap.Remove(WidgetName);
}
