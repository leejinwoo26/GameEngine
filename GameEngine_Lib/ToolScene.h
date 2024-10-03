#pragma once
#include "..\\GameEngine_Source\\Scene.h"	
#include "..\\GameEngine_Lib\\Tile.h"

namespace GE
{
	class ToolScene: public Scene
	{
	public:
		ToolScene();
		~ToolScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Destroy() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void Save();
		void Load();
	private:
		std::vector<Tile*> mTiles;
	};
}