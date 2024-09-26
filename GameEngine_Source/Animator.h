#pragma once
#include "Component.h"
#include "Animation.h"
#include "Texture.h"

namespace GE
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator =(std::function<void()> func)
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

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event EndEvent;
		};


		Animator();
		~Animator();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name,
			Texture* spriteSheet,
			Vector2 leftTop,
			Vector2 size,
			Vector2 offset,
			UINT spriteLeghth,
			float duration);
		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		Events* FindEvent(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);


	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop;

		std::map<const std::wstring, Events*> mEvents;
	};
}