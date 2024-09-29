#pragma once
#include "Collider.h"

namespace GE
{
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
	public:
		Vector2 GetBoxCollsionSize() { return mBoxCollisionSize; }
		void SetBoxCollsionSize(Vector2 boxCollsionSize) { mBoxCollisionSize = boxCollsionSize; }

	private:
		Vector2 mBoxCollisionSize;
	};

}