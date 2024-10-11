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
	std::vector<Animation*> AnimationScene::mAnimations = {};

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

		Print_Text(hdc, L"�� ���ӿ�����Ʈ ���� ", (int)AnimationScene::GetLayer(eLayerType::ANIMATIONCLIP)->GetGameObjects().size()
			, Vector2(1400, 450));
		Vector2 cameraPos = mainCamera->GetCameraPosition();

		Print_Text(hdc, L"���콺 Y ",Input::GetMousePosition().y /*+ cameraPos.y*/, Vector2(1400, 500));
		Print_Text(hdc, L"���콺 X ",Input::GetMousePosition().x /*+ cameraPos.x*/, Vector2(1400, 550));
		Print_Text(hdc, L"�ؽ�ó �ε��� ", (int)mTextureIndex, Vector2(1400, 750));
		Print_Text(hdc, L"�ε��� �� : O ", Vector2(1400, 800));
		Print_Text(hdc, L"�ε��� �ٿ� : P ", Vector2(1400, 850));

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
		OPENFILENAME ofn = {};
		wchar_t szFilePath[256] = {};
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFilePath);
		ofn.lpstrFilter = L"Binary Files\0*.bin\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

		if (GetSaveFileName(&ofn)) {
			std::ofstream outFile(szFilePath, std::ios::binary);

			if (!outFile) {
				// ���� ���� ���� ó��
				return;
			}

			// mAnimCuts�� �� AnimCut ������ ����
			size_t count = mActiveAnimation->GetSprite().size();
			outFile.write(reinterpret_cast<const char*>(&count), sizeof(count)); // AnimCut ���� ����

			std::wstring texturePath = mActiveAnimation->GetTexture()->GetFilePath(); // GetFilePath() �޼��� �ʿ�
			size_t pathLength = texturePath.length();
			outFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength)); // ��� ���� ����
			outFile.write(reinterpret_cast<const char*>(texturePath.c_str()), pathLength * sizeof(wchar_t)); // wchar_t�� ��� ����

			for (const auto& animCut : mActiveAnimation->GetSprite()) 
			{
				outFile.write(reinterpret_cast<const char*>(&animCut.leftTop), sizeof(Vector2));
				outFile.write(reinterpret_cast<const char*>(&animCut.Size), sizeof(Vector2));
				outFile.write(reinterpret_cast<const char*>(&animCut.Offset), sizeof(Vector2));
				outFile.write(reinterpret_cast<const char*>(&animCut.duration), sizeof(float));
			}
			outFile.close(); // ���� �ݱ�
		}

	}
	void AnimationScene::Load()
	{
		OPENFILENAME ofn = {};
		wchar_t szFilePath[256] = {};
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFilePath);
		ofn.lpstrFilter = L"Binary Files\0*.bin\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn)) {
			std::ifstream inFile(szFilePath, std::ios::binary);

			if (!inFile) {
				// ���� ���� ���� ó��
				return;
			}

			// AnimCut ���� �б�
			size_t count = 0;
			inFile.read(reinterpret_cast<char*>(&count), sizeof(count));

			std::wstring fullPath(szFilePath);
			std::wstring fileName = fullPath.substr(fullPath.find_last_of(L"\\") + 1);

			size_t dotIndex = fileName.find_last_of(L".");
			if (dotIndex != std::wstring::npos) {
				fileName = fileName.substr(0, dotIndex); // Ȯ���� �ձ��� �߶�
			}


			Animation* animation = new Animation();

			size_t pathLength;
			inFile.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
			std::wstring texturePath(pathLength, L'\0'); // �ؽ�ó ��θ� ���� ����
			inFile.read(reinterpret_cast<char*>(&texturePath[0]), pathLength * sizeof(wchar_t)); // wchar_t�� �б�

			// �ؽ�ó ����
			Texture* texture = new Texture();
			texture->Load(texturePath); // ��θ� ���� �ؽ�ó �ε�
			animation->SetTexture(texture);

			for (size_t i = 0; i < count; ++i) {
				AnimCut* animCut = new AnimCut(); // ���ο� AnimCut ��ü ����

				// AnimCut ���� �б�
				Vector2 leftTop;
				Vector2 size;
				Vector2 offSet;
				float Duration;

				inFile.read(reinterpret_cast<char*>(&leftTop), sizeof(Vector2));
				inFile.read(reinterpret_cast<char*>(&size), sizeof(Vector2));
				inFile.read(reinterpret_cast<char*>(&offSet), sizeof(Vector2));
				inFile.read(reinterpret_cast<char*>(&Duration), sizeof(float));

				Animation::Sprite sprite = {};
				sprite.leftTop = leftTop;
				sprite.Size = size;
				sprite.Offset = offSet;
				sprite.duration = Duration;

				animation->GetSprite().push_back(sprite);
			}
			animation->SetName(fileName);
			mAnimations.push_back(animation);
			inFile.close(); // ���� �ݱ�
		}
	}
	void AnimationScene::CreateAnimation()
	{
		if (mAnimCuts.size() <= 0)
			return;

		Texture* mTexture = mTextures[mTextureIndex];

		Vector2 cameraPos =  mainCamera->GetCameraPosition();
		for (int i = 0; i < mAnimCuts.size(); i++)
		{
			Animation::Sprite sprite = {};
			sprite.leftTop.x = mAnimCuts[i]->GetOriginPos().x;
			sprite.leftTop.y = mAnimCuts[i]->GetOriginPos().y;
			sprite.leftTop.y = min(79, max(sprite.leftTop.y, 1));

			sprite.Size = mAnimCuts[i]->GetCutSize();
			sprite.Offset = Vector2(0,0);
			sprite.duration = 0.3;

			mActiveAnimation->GetSprite().push_back(sprite);
		}

		mAnimCuts.clear();
		ClearClips();
	}
	void AnimationScene::AddFrame_Animation()
	{
		Vector2 cameraPos = mainCamera->GetCameraPosition();
		
		Animation::Sprite sprite = {};
		sprite.leftTop.x = ActiveAnimCut->GetOriginPos().x;
		sprite.leftTop.y = ActiveAnimCut->GetOriginPos().y;
		sprite.Size = ActiveAnimCut->GetCutSize();
		sprite.Offset = Vector2(0, 0);
		sprite.duration = 0.2;
		mActiveAnimation->GetSprite().push_back(sprite);

		mAnimCuts.clear();
		ClearClips();
	}

	void AnimationScene::PlayAnimation_Animator()
	{
		mAnimator->SetActiveAnimation(mActiveAnimation);
		mActiveAnimation->SetTexture(mTextures[mTextureIndex]);
		mActiveAnimation->SetAnimator(mAnimator);
		mAnimator->SetLoop(true);
		mAnimator->PlayAnimation_Tool(mActiveAnimation);
	}

	void AnimationScene::ActiveAnimationClear()
	{
		mActiveAnimation->GetSprite().clear();
		mActiveAnimation->Reset();
	}

	void AnimationScene::ClearClips()
	{
		AnimationScene::GetLayer(eLayerType::ANIMATIONCLIP)->Clear_AnimClip();
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

		//�̰� ī�޶�� ����

		GameObject* camera2 = Instantiate<GameObject>(eLayerType::CAMERA, Vector2(0, 0));
		cameraScript = camera2->AddComponent<CameraScript>();
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

		if (mActiveAnimation->GetToolMode() == true)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				++mActiveAnimation->GetSprite()[0].leftTop.y;
			}

			if (Input::GetKey(eKeyCode::L))
			{
				--mActiveAnimation->GetSprite()[0].leftTop.y;
			}

			if (Input::GetKeyDown(eKeyCode::P))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				int animSize = mActiveAnimation->GetSprite().size() - 1;
				if (activeIndex >= animSize)
					return;
				activeIndex++;
				mActiveAnimation->SetAnimIndex(activeIndex);
			}
			if (Input::GetKeyDown(eKeyCode::O))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				if (activeIndex<=0)
					return;
				activeIndex--;
				mActiveAnimation->SetAnimIndex(activeIndex);
			}
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				float offsetX = mActiveAnimation->GetSprite()[activeIndex].Offset.x;
				offsetX++;
				mActiveAnimation->GetSprite()[activeIndex].Offset.x = offsetX;
			}
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				float offsetX = mActiveAnimation->GetSprite()[activeIndex].Offset.x;
				offsetX--;
				mActiveAnimation->GetSprite()[activeIndex].Offset.x = offsetX;
			}
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				float offsetY = mActiveAnimation->GetSprite()[activeIndex].Offset.y;
				offsetY--;
				mActiveAnimation->GetSprite()[activeIndex].Offset.y = offsetY;
			}
			if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				int activeIndex = mActiveAnimation->GetAnimIndex();
				float offsetY = mActiveAnimation->GetSprite()[activeIndex].Offset.y;
				offsetY++;
				mActiveAnimation->GetSprite()[activeIndex].Offset.y = offsetY;
			}
		}
		else
		{
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
		}
		

		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::Z))//�ִϸ��̼� ����
		{
			CreateAnimation();
		}
		if (Input::GetKeyDown(eKeyCode::V))//����
		{
			PlayAnimation_Animator();
		}
		if (Input::GetKeyDown(eKeyCode::N))//�ִϸ��̼� Ŭ����
		{
			ActiveAnimationClear();
		}
		if (Input::GetKeyDown(eKeyCode::L))//�ε�
		{
			AnimationScene::Load();
		}
		


		if (Input::GetKeyDown(eKeyCode::M))//���� ���
		{
			if (mActiveAnimation->GetToolMode() == true)
			{
				cameraScript->SetEnable(true);
				mActiveAnimation->SetToolMode(false);//������� ���
			}
			else
			{
				cameraScript->SetEnable(false);
				mActiveAnimation->SetToolMode(true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))//��Ʈ Ŭ�� Ŭ����
		{
			ClearClips();
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			ActiveAnimCut = Instantiate<AnimCut>(eLayerType::ANIMATIONCLIP);
			Vector2 cameraPos = mainCamera->GetCameraPosition();
			ActiveAnimCut->SetOriginPos(Input::GetMousePosition() + cameraPos);
			ActiveAnimCut->SetSecondPos(Input::GetMousePosition() + cameraPos);
		}
		if (Input::GetKey(eKeyCode::LBUTTON))
		{
			Vector2 cameraPos = mainCamera->GetCameraPosition();
			ActiveAnimCut->SetSecondPos(Input::GetMousePosition() + cameraPos);
		}
		if (Input::GetKeyUp(eKeyCode::LBUTTON))
		{
			mAnimCuts.push_back(ActiveAnimCut);
		}


	}
}