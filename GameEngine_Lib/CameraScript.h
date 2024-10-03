#pragma once
#include "..\\GameEngine_Source\\Script.h"

namespace GE
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);


		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

	private:
	};
}