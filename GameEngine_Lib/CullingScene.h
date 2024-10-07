#pragma once
#include "..\\GameEngine_Source\\Scene.h"
namespace GE
{
	class CullingScene : public Scene
	{
	public:
		CullingScene();
		~CullingScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;
	private:
	};
}
