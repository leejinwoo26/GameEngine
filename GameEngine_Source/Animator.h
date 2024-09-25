#pragma once
#include "Component.h"
#include "Animation.h"
#include "Texture.h"

namespace GE
{
	class Animator : public Component
	{
	public:
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

	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop;
	};
}