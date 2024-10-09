#include "GameObject.h"
#include "Input.h"
#include "Transform.h"


namespace GE
{
	GameObject::GameObject():
		mState(eState::ACTIVE),
		mLayerType(eLayerType::NONE)
	{
		mComponents.resize((UINT)eComponentType::END);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}
		if (mtarget)
		{
			Transform* tr = GetComponent<Transform>();

			Transform* targetTr = mtarget->GetComponent<Transform>();
			Vector2 targetPos = targetTr->GetPosition();

			Vector2 offset1(-2.5, 15); 
			Vector2 newPos = targetPos + offset1;
			tr->SetPos(newPos);
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
		}
	}
}