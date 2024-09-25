#pragma once
#include "Entity.h"

namespace GE
{
	class GameObject;

	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { mOwner = owner; };
		GameObject* GetOwner() { return mOwner; }
		eComponentType GetComponentType() { return mType; }

	private:
		GameObject* mOwner;
		eComponentType mType;
	};

}