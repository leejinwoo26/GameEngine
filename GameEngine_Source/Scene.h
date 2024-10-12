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
		void CreateTileBuffer(Vector2 tileCount);
		void RenderTiles();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, eLayerType type);
		void EraseGameObject(GameObject* gameObj);

		void Load();
		void LoadTileMap(const std::wstring& path, const std::wstring& name);

		const std::vector<std::vector<class Tile*>>& GetTiles() { return mTiles; }
		Layer* GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<std::vector<class Tile*>> mTiles;
		Vector2 mSize;
		Vector2 mTileCount;

		std::vector<Layer*> mLayers;
	};
}
