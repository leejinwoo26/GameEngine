#pragma once
#include "..\\GameEngine_Source\\GameObject.h"

namespace GE
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();
		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);
	private:
	};

}