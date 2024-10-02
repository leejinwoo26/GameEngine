#pragma once
#include "GameObject.h"


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
		void SetPos(int x, int y);
	private:

	};
}