#pragma once
#include "Collider.h"

namespace GE 
{
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();
		~CircleCollider2D();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		float GetRadius() { return mRadius; }
		void SetRadius(float rad) { mRadius = rad; }
	private:
		float mRadius;
	};
}