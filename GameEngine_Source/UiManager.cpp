#include "UiManager.h"
#include "UIHUD.h"
#include "UIButton.h"

namespace GE
{
	std::unordered_map<eUIType, UiBase*> UiManager::mUIs = {};
	std::stack<UiBase*> UiManager::mUiBases = {};
	std::queue<eUIType> UiManager::mRequestUiQueues = {};
	UiBase* UiManager::mActiveUI = nullptr;

	UiManager::UiManager()
	{
	}
	UiManager::~UiManager()
	{
	}
	void UiManager::Initialize()
	{
		UIHUD* hud = new UIHUD();
		mUIs.insert(std::make_pair(eUIType::HPBAR, hud));
		UiManager::Push(eUIType::HPBAR);

		UIButton* button = new UIButton();
		mUIs.insert(std::make_pair(eUIType::BUTTON, button));
		UiManager::Push(eUIType::BUTTON);
    }
	void UiManager::OnLoad(eUIType type)
	{
		auto iter = mUIs.find(type);

		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}
		OnComplete(iter->second);
	}
	void UiManager::Update()
	{
		std::stack<UiBase*> uiBases = mUiBases;
		while (uiBases.empty() == false)
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Update();
				uiBases.pop();
			}
		}

		if (mRequestUiQueues.size() > 0)
		{
			eUIType requestType = mRequestUiQueues.front();
			mRequestUiQueues.pop();
			OnLoad(requestType);
		}
	}
	void UiManager::LateUpdate()
	{
		std::stack<UiBase*> uiBases = mUiBases;
		while (uiBases.empty() == false)
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}
	void UiManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUiBases;
		while (uiBases.empty() == false)
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Render(hdc);
				uiBases.pop();
			}
		}
	}
	void UiManager::OnComplete(UiBase* addUi)
	{
		if (addUi == nullptr)
			return;

		addUi->Initialize();
		addUi->Active();
		addUi->Update();

		if (addUi->IsFullScreen())
		{
			std::stack<UiBase*> uiBases = mUiBases;
			while (uiBases.empty() == false)
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase)
				{
					uiBase->InActive();
				}
			}
		}
		mUiBases.push(addUi);
		mActiveUI = nullptr;
	}
	void UiManager::OnFail()
	{
		mActiveUI = nullptr;
	}
	void UiManager::Release()
	{
		for (auto iter : mUIs)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void UiManager::Push(eUIType type)
	{
		mRequestUiQueues.push(type);
	}

	void UiManager::Pop(eUIType type)
	{
		if (mUiBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;

		while (mUiBases.size() > 0)
		{
			uiBase = mUiBases.top();
			mUiBases.pop();
			if (uiBase->GetType() != type)
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen())
			{
				std::stack<UiBase*> uiBases = mUiBases;
				while (!uiBases.empty())
				{
					UiBase* uiBase = uiBases.top();
					uiBases.pop();
					if (uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}
		}
		while (tempStack.size() > 0)
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUiBases.push(uiBase);
		}
	}
}