#pragma once
#include "CommonInclude.h"
#include "Component.h"

namespace GE
{
	class GameObject
	{
	public:
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
			mComponents.push_back(component);
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

	private:
		std::vector<Component*> mComponents;
	};
}

