#pragma once
#include "..\\GameEngine_Source\\GameObject.h"

namespace GE
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		void SetIndexPos(int x, int y);
	private:
	};
}