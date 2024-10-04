#pragma once
#include "Entity.h"

namespace GE 
{
	class UiBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

		UiBase(eUIType type);
		virtual ~UiBase();
		void Initialize();
		void Active();
		void InActive();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnClear();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC hdc);

		eUIType GetType() { return mType; }
		void SetType(eUIType type) { mType = type; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() { return mbFullScreen; }
		Vector2 GetPos() { return mPosition; }
		void SetPos(Vector2 position) { mPosition = position; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }

	protected:
		Vector2 mPosition;
		Vector2 mSize;
		bool mbMouseOn;

	private:
		eUIType mType;
		bool mbFullScreen;
		bool mbEnabled;

		UiBase* mParent;
	};
}