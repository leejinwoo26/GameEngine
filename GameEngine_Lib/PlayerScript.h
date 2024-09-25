#pragma once
#include "..\\GameEngine_Source\\Script.h"

namespace GE
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

	private:


	};

}