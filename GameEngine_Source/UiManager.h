#pragma once
#include "UiBase.h"
#include "CommonInclude.h"

namespace GE
{
	class UiManager
	{
	public:
		UiManager();
		~UiManager();
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void OnComplete(UiBase* addUi);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

	private:
		static std::unordered_map<eUIType, UiBase*> mUIs;
		static std::stack<UiBase*> mUiBases;  
		static std::queue<eUIType> mRequestUiQueues;
		static UiBase* mActiveUI;
	};  
}