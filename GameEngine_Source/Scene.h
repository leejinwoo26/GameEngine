#pragma once
#include "Entity.h"
#include "GameObject.h"

namespace GE
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObj);
	private:
		std::vector<GameObject*> mGameObjs;
	};
}
