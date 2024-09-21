#pragma once
#include "Component.h"

namespace GE
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};
}