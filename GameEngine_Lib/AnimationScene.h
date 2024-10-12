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

	public:
		void Save();
		static void Load();
		static void LoadAllFromFolder(const std::wstring& folderPath);


	public:
		void CreateAnimation();
		void AddFrame_Animation();
		void PlayAnimation_Animator();
		void ActiveAnimationClear();
		void ClearClips();


	public:
		static const std::map<std::wstring, Animation*>& GetAnimations_Map() { return mAnimations_map; }

	private:
		void TextureInit();
		void CameraInit();
		void AnimatorInit();
		void InputUpdate();
	private:
		static std::map<std::wstring, Animation*> mAnimations_map;
		std::vector<class AnimCut*> mAnimCuts;
		std::vector<Animation::Sprite> mAnimationSheet;
		Animation* mActiveAnimation;
	private:
		class AnimCut* ActiveAnimCut;
		class Animator* mAnimator;
	private:
		GameObject* animator;
		GameObject* mTexObj;
	private:
		std::vector<class Texture*> mTextures;
		SpriteRenderer* mSpriteRenderer;
	private:
		class CameraScript* cameraScript;
	private:
		UINT mTextureIndex;
	};

}