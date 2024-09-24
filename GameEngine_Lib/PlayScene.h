#pragma once
#include "..\\GameEngine_Source\\Scene.h"
#include "Player.h"

namespace GE
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();
		void Initialize() override;	
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;
	private:
		Player* bg;
	};
}