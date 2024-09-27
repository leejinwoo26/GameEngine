#pragma once
#include "Entity.h"
#include "CommonInclude.h"
#include "GameObject.h"

namespace GE
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();
		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);
		void Destroy();

		void AddGameObject(GameObject* gameObj);

	private:
		std::vector<GameObject*> mGameObjs;
		std::vector<GameObject*> mDestroyObjs;
	};
}

