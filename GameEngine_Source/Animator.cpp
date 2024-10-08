#include "Animator.h"
#include "Texture.h"
#include "Resources.h"

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

	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
	{
		//Animation* animation = nullptr;
		//animation = FindAnimation(name);
		//if (animation != nullptr)
		//	return;
		////D:\JunJae\AR50\YamYam_Engine\Resources\Mushroom\1.bmp
		//int fileCount = 0;
		//std::filesystem::path fs(path);
		//std::vector<Texture*> images = {};
		//for (auto& p : std::filesystem::recursive_directory_iterator(fs))
		//{
		//	std::wstring fileName = p.path().filename();
		//	std::wstring fullName = p.path();

		//	Texture* texture = Resources::Load<Texture>(fileName, fullName);
		//	images.push_back(texture);
		//	fileCount++;
		//}


		//UINT sheetWidth = images[0]->GetWidth() * fileCount;
		//UINT sheetHeight = images[0]->GetHeight();
		//Texture* spriteSheet = Texture::Create(name, sheetWidth, sheetHeight);

		//UINT imageWidth = images[0]->GetWidth();
		//UINT imageHeight = images[0]->GetHeight();
		//for (size_t i = 0; i < images.size(); i++)
		//{
		//	BitBlt(spriteSheet->GetHdc(), i * imageWidth, 0
		//		, imageWidth, imageHeight
		//		, images[i]->GetHdc(), 0, 0, SRCCOPY);
		//}

		//CreateAnimation(name, spriteSheet
		//	, Vector2(0.0f, 0.0f), Vector2(imageWidth, imageHeight)
		//	, offset, fileCount, duration);
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