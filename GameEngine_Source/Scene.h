#pragma once
#include "Entity.h"
#include "Layer.h"
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
		virtual void Destroy();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj,eLayerType type);
		void EraseGameObject(GameObject* gameObj);

		Layer* GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<Layer*> mLayers;
	};
}
