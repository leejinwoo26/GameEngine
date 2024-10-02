#pragma once
#include "Component.h"
#include "Texture.h"
#include "Entity.h"

namespace GE
{
	class TileRenderer : public Component
	{
	public:
		TileRenderer();
		~TileRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetTexture(Texture* texture) { mTexture = texture; }
		void SetSize(Vector2 size) { mSize = size; }
		Texture* GetTexture() { return mTexture; }
		static Vector2 GetTileSize() { return TileSize; }
	private:
		static Vector2 TileSize;

		Texture* mTexture;
		Vector2 mSize;
		Vector2 mIndex;
		Vector2 mTileSize;
	};
}