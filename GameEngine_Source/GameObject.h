#pragma once
#include "CommonInclude.h"
#include "Component.h"

namespace GE
{
	class GameObject
	{
	public:
		enum class eState
		{
			ACTIVE,
			PAUSE,
			DEAD,
			END
		};

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		GameObject();
		~GameObject();

		template <typename T>
		T* AddComponent()
		{
			T* component = new T;
			component->SetOwner(this);
			component->Initialize();

			mComponents[(UINT)component->GetComponentType()] = component;
			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}
			return component;
		}

		void SetActive(bool active)
		{
			if (active == true) mState = eState::ACTIVE;
			else if (active == false) mState = eState::PAUSE;
		}
		void Death() { mState = eState::DEAD; }
		eState GetState() { return mState; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}

