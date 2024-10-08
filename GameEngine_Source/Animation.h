#pragma once
#include "Resource.h"
#include "Texture.h"

namespace GE
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 Size;
			Vector2 Offset;
			float duration;

			Sprite():
				leftTop(Vector2(0.f,0.f)),
				Size(Vector2(0.f, 0.f)),
				Offset(Vector2(0.f, 0.f)),
				duration(0.f)
			{
			}
		};
		Animation();
		~Animation();
		virtual HRESULT Load(const std::wstring& path) override;

		void CreateAnimation(const std::wstring& name,
			Texture* spriteSheet,
			Vector2 leftTop,
			Vector2 size,
			Vector2 offset,
			UINT spriteLeghth,
			float duration);

		void Update();
		void Render(HDC hdc);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

		int GetIndex() { return mIndex; }
		std::vector<Sprite>& GetSprite() { return mAnimationSheet; }

	private:
		class Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mAnimationSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}