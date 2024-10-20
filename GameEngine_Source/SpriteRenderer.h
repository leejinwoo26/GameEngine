#pragma once
#include "Component.h"
#include "Texture.h"


namespace GE
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		__forceinline void SetTexture(Texture* texture) { mTexture = texture; }
		__forceinline void SetSize(Vector2 size) { mSize = size; }
		Texture* GetTexture() { return mTexture; }
		Vector2& GetSize() { return mSize; }
	private:
		Texture* mTexture;
		Vector2 mSize;
	};
}


