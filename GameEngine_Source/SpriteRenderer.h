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

		void SetTexture(Texture* texture) { mTexture = texture; }
		void SetSize(Vector2 size) { mSize = size; }
		Texture* GetTexture() { return mTexture; }

	private:
		Texture* mTexture;
		Vector2 mSize;
	};
}


