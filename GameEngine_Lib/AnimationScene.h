#pragma once
#include "..\\GameEngine_Source\\Scene.h"
#include "..\\GameEngine_Source\\SpriteRenderer.h"
#include "..\\GameEngine_Source\\Animation.h"
#include "..\\GameEngine_Source\\Animator.h"

namespace GE
{
	class AnimationScene : public Scene
	{
	public:
		AnimationScene();
		~AnimationScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		void Save();
		void CreateAnimation();
		void AddFrame_Animation();
		void PlayAnimation_Animator();
		void ActiveAnimationClear();
		void ClearClips();

	private:
		void TextureInit();
		void CameraInit();
		void AnimatorInit();
		void InputUpdate();
	private:
		std::vector<class Texture*> mTextures;
		SpriteRenderer* mSpriteRenderer;
		GameObject* mTexObj;
		UINT mTextureIndex;
		class AnimCut* ActiveAnimCut;
		std::vector<class AnimCut*> mAnimCuts;

		Animation* mActiveAnimation;
		class Animator* mAnimator;
		std::vector<Animation::Sprite> mAnimationSheet;
		GameObject* animator;
	};

}