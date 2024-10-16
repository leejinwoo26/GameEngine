#include "pch.h"
#include "Animator.h"
#include "Texture.h"
#include "Resources.h"
#include "..\\GameEngine_Lib\\AnimationScene.h"
#include "AnimCut.h"

namespace GE
{
	Animator::Animator():
		Component(eComponentType::ANIMATOR),
		mAnimations{},
		mActiveAnimation(nullptr),
		mbLoop(false)
	{
	}

	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		mActiveAnimation = nullptr;
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			mActiveAnimation->GetName();
			Events* events = FindEvent(mActiveAnimation->GetName());

			if (mActiveAnimation->IsComplete())
			{
				if (events)
					events->completeEvent();
				if(mbLoop ==true)
					mActiveAnimation->Reset();
			}
		}
	}

	void Animator::LateUpdate()
	{
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLeghth, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->CreateAnimation(name, spriteSheet,
			leftTop, size, offset, spriteLeghth, duration);
		animation->SetAnimator(this);
		animation->SetName(name);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		mAnimations.insert(std::make_pair(name, animation));
	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* spriteSheet, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->CreateAnimation(name, spriteSheet, duration);
		animation->SetAnimator(this);
		animation->SetName(name);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		mAnimations.insert(std::make_pair(name, animation));
	}

	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
	{
	}

	void Animator::AddAnimation(const std::wstring& name)
	{
		const auto& animations_map =  AnimationScene::GetAnimations_Map();

		auto iter = animations_map.find(name);
		if (iter == animations_map.end())
			return;

		iter->second->SetAnimator(this);
		mAnimations.insert({ name,iter->second });

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	void Animator::AddAnimation_Bulk(const std::wstring& path)
	{
		WIN32_FIND_DATA findFileData;
		HANDLE hFind = FindFirstFile((path + L"\\*.bin").c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE) {
			std::wcerr << L"Error: No .bin files found in the directory." << std::endl;
			return;
		}

		do {
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::wstring filePath = path + L"\\" + findFileData.cFileName;

				std::wcout << L"Loading: " << filePath << std::endl;
				std::ifstream inFile(filePath, std::ios::binary);
				if (!inFile) {
					std::wcerr << L"Error: Could not open file " << findFileData.cFileName << std::endl;
					continue; 
				}

				// AnimCut 개수 읽기
				size_t count = 0;
				inFile.read(reinterpret_cast<char*>(&count), sizeof(count));

				std::wstring fullPath(filePath);
				std::wstring fileName = fullPath.substr(fullPath.find_last_of(L"\\") + 1);

				size_t dotIndex = fileName.find_last_of(L".");
				if (dotIndex != std::wstring::npos) {
					fileName = fileName.substr(0, dotIndex); // 확장자 앞까지 잘라냄
				}

				Animation* animation = new Animation();

				size_t pathLength;
				inFile.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
				std::wstring texturePath(pathLength, L'\0');
				inFile.read(reinterpret_cast<char*>(&texturePath[0]), pathLength * sizeof(wchar_t));

				// 텍스처 생성
				Texture* texture = new Texture();
				texture->Load(texturePath);
				animation->SetTexture(texture);


				for (size_t i = 0; i < count; ++i) {
					//AnimCut* animCut = new AnimCut(); // 새로운 AnimCut 객체 생성

					// AnimCut 정보 읽기
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
				animation->SetAnimator(this);
				mAnimations.insert({ fileName, animation });
				inFile.close(); // 파일 닫기
			}

		} while (FindNextFile(hFind, &findFileData) != 0);

		FindClose(hFind);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;
		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;
		
		if (mActiveAnimation)
		{
			Events* currentEvents = FindEvent(mActiveAnimation->GetName());
			if (currentEvents)
				currentEvents->EndEvent();
		}

		Events* nextEvent = FindEvent(animation->GetName());
		if (nextEvent)
			nextEvent->startEvent();

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
	void Animator::PlayAnimation_Tool(Animation* anim)
	{
		mActiveAnimation->Reset();
		mActiveAnimation = anim;
	}
	Animator::Events* Animator::FindEvent(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvent(name);
		return events->startEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvent(name);
		return events->completeEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvent(name);
		return events->EndEvent.mEvent;
	}
}