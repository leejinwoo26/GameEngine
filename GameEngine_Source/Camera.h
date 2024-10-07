#pragma once
#include "Component.h"
#include "GameObject.h"


namespace GE
{
	class Camera : public Component
	{
	public:
		Vector2 CalculatePosition(Vector2 pos) { return pos- mDistance; }


		Camera();
		~Camera();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;
		void SetTarget(GameObject* target) { mTarget = target;}
		GameObject* GetTarget()
		{
			if (mTarget == nullptr)
				return nullptr;
			return mTarget;
		}
		Vector2 GetCameraPosition();

	private:
		Vector2 mDistance;
		Vector2 mResolution;
		Vector2 mLookPosition;
		GameObject* mTarget;
	};

}