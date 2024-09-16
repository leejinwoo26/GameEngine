#pragma once
#include "CommonInclude.h"

namespace GE
{
	class GameObject
	{
	public:
		void Initilize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		GameObject();
		~GameObject();
	private:
		float xSpeed;
	};
}

