#include "AnimationScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Renderer.h"
#include "Object.h"
#include "CameraScript.h"
#include "Input.h"
#include "Resources.h"
#include "Debug_Text.h"
#include "..\\GameEngine_Source\\AnimCut.h"





namespace GE 
{
	AnimationScene::AnimationScene():
		mTextureIndex(0),
		mTextures{},
		mSpriteRenderer(nullptr)
	{
		
	}
	AnimationScene::~AnimationScene()
	{
	}
	void AnimationScene::Initialize()
	{
		CameraInit();
		TextureInit();
		AnimatorInit();



		Scene::Initialize();
	}
	void AnimationScene::Update()
	{
		Scene::Update();



		InputUpdate();
	}
	void AnimationScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void AnimationScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Print_Text(hdc, L"텍스처 인덱스 ", (int)mTextureIndex, Vector2(1400, 750));
		Print_Text(hdc, L"인덱스 업 : O ", Vector2(1400, 800));
		Print_Text(hdc, L"인덱스 다운 : P ", Vector2(1400, 850));
		Print_Text(hdc, L"마우스 Y ",Input::GetMousePosition().y, Vector2(1400, 500));
		Print_Text(hdc, L"마우스 X ",Input::GetMousePosition().x, Vector2(1400, 550));


		
		Print_Text(hdc, L"총 게임오브젝트 갯수 ", (int)AnimationScene::GetLayer(eLayerType::ANIMATIONCLIP)->GetGameObjects().size()
			, Vector2(1400, 300));

	}
	void AnimationScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void AnimationScene::OnExit()
	{
		Scene::OnExit();
	}
	void AnimationScene::Save()
	{
		std::ofstream outFile("animCuts.bin", std::ios::binary | std::ios::app); // 이진 모드로 파일 열기 , 덮어씌우기

		if (!outFile) {
			// 파일 열기 실패 처리
			return;
		}

		// mAnimCuts의 각 AnimCut 정보를 저장
		size_t count = mAnimCuts.size();
		outFile.write(reinterpret_cast<const char*>(&count), sizeof(count)); // AnimCut 개수 저장

		for (const auto& animCut : mAnimCuts) {
			if (animCut) { // nullptr 체크
				// AnimCut 정보를 이진 형식으로 저장
				outFile.write(reinterpret_cast<const char*>(&animCut->GetOriginPos()), sizeof(Vector2));
				outFile.write(reinterpret_cast<const char*>(&animCut->GetSecondPos()), sizeof(Vector2));
				outFile.write(reinterpret_cast<const char*>(&animCut->GetCutSize()), sizeof(Vector2));
			}
		}

		outFile.close(); // 파일 닫기

	}
	void AnimationScene::CreateAnimation()
	{
		Texture* mTexture = mTextures[mTextureIndex];

		Vector2 cameraPos =  mainCamera->GetCameraPosition();
		for (int i = 0; i < mAnimCuts.size(); i++)
		{
			Animation::Sprite sprite = {};
			sprite.leftTop.x = mAnimCuts[i]->GetOriginPos().x + cameraPos.x;
			sprite.leftTop.y = mAnimCuts[i]->GetOriginPos().y + cameraPos.y;
			sprite.Size = mAnimCuts[i]->GetCutSize();
			sprite.Offset = Vector2(0,0);
			sprite.duration = 0.2;

			mAnimationSheet.push_back(sprite);
		}

	}
	void AnimationScene::AddFrame_Animation()
	{
		Vector2 cameraPos = mainCamera->GetCameraPosition();
		
		Animation::Sprite sprite = {};
		sprite.leftTop.x = ActiveAnimCut->GetOriginPos().x + cameraPos.x;
		sprite.leftTop.y = ActiveAnimCut->GetOriginPos().y + cameraPos.y;
		sprite.Size = ActiveAnimCut->GetCutSize();
		sprite.Offset = Vector2(0, 0);
		sprite.duration = 0.2;
		mActiveAnimation->GetSprite().push_back(sprite);

	}
	void AnimationScene::SetAnimation_Animator()
	{
		mAnimator->SetActiveAnimation(mActiveAnimation);
	}

	void AnimationScene::PlayAnimation_Animator()
	{
		mActiveAnimation->SetTexture(mTextures[mTextureIndex]);
		mActiveAnimation->SetAnimator(mAnimator);
		mAnimator->SetLoop(true);
		mAnimator->PlayAnimation_Tool(mActiveAnimation);
	}

	void AnimationScene::ActiveAnimationClear()
	{
		delete mActiveAnimation;
		mActiveAnimation = nullptr;
		delete mAnimator;
		mAnimator = nullptr;
	}


	void AnimationScene::TextureInit()
	{
		auto resources = Resources::GetResources();
		mTextures.reserve(resources.size());

		for (auto iter = resources.begin(); iter != resources.end(); iter++)
		{
			mTextures.push_back((Texture*)iter->second);
		}

		mTexObj = Instantiate<GameObject>(eLayerType::BACKGROUND, Vector2(0, 0));
		mSpriteRenderer = mTexObj->AddComponent<SpriteRenderer>();

		mSpriteRenderer->SetTexture(mTextures[mTextureIndex]);
	}
	void AnimationScene::CameraInit()
	{
		GameObject* camera = Instantiate<GameObject>(eLayerType::CAMERA, Vector2(0, 0));
		Camera* cameraComp = camera->AddComponent<Camera>();
		mainCamera = cameraComp;

		//이걸 카메라로 셋팅

		GameObject* camera2 = Instantiate<GameObject>(eLayerType::CAMERA, Vector2(0, 0));
		camera2->AddComponent<CameraScript>();
		mainCamera->SetTarget(camera2);
	}
	void AnimationScene::AnimatorInit()
	{
		mActiveAnimation = new Animation();
		mAnimator = new Animator();

		animator = Instantiate<GameObject>(eLayerType::ANIMATOR, Vector2(500, 500));
		mAnimator = animator->AddComponent<Animator>();
	}
	void AnimationScene::InputUpdate()
	{
		if (Input::GetKeyDown(eKeyCode::I))
		{
			mSpriteRenderer->SetTexture(mTextures[mTextureIndex]);
		}
		if (Input::GetKeyDown(eKeyCode::P))
		{
			if (mTextureIndex < mTextures.size() - 1)
			{
				mTextureIndex++;
				mSpriteRenderer->SetTexture(mTextures[mTextureIndex]);
			}
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			if (mTextureIndex > 0)
			{
				mTextureIndex--;
				mSpriteRenderer->SetTexture(mTextures[mTextureIndex]);
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			AddFrame_Animation();
		}
		if (Input::GetKeyDown(eKeyCode::V))
		{
			SetAnimation_Animator();
		}
		if (Input::GetKeyDown(eKeyCode::B))
		{
			PlayAnimation_Animator();
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			ActiveAnimationClear();
		}




		if (Input::GetKeyDown(eKeyCode::C))
		{
			AnimationScene::GetLayer(eLayerType::ANIMATIONCLIP)->Clear_AnimClip();
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			ActiveAnimCut = Instantiate<AnimCut>(eLayerType::ANIMATIONCLIP);
			ActiveAnimCut->SetOriginPos(Input::GetMousePosition());
			ActiveAnimCut->SetSecondPos(Input::GetMousePosition());
		}
		if (Input::GetKey(eKeyCode::LBUTTON))
		{
			ActiveAnimCut->SetSecondPos(Input::GetMousePosition());
		}
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			mAnimCuts.push_back(ActiveAnimCut);
		}


	}
}