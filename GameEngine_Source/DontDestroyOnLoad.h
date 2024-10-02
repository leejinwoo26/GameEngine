#pragma once
#include "Scene.h"
namespace GE
{
	class DontDestroyOnLoad : public Scene
	{
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Destroy() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}

