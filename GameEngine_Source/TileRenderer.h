#pragma once
#include "Component.h"
#include "Texture.h"
#include "Entity.h"
#include "CommonInclude.h"
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
		void SetIndex(Vector2 index) { mIndex = index; }
		Texture* GetTexture() { return mTexture; }
		static const Vector2& GetTileSize() { return TileSize; }

		Vector2 GetIndex() { return mIndex; }

	public:
		static Vector2 TileSize;
		static Vector2 OriginTileSize;
		static Vector2 SelectedIndex;

	private:
		Vector2 mTileSize;
		Vector2 mSize;
		Texture* mTexture;
		Vector2 mIndex;
	};
}