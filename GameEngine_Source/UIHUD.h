#pragma once
#include "UiBase.h"
#include "Texture.h"

namespace GE
{
	class UIHUD : public UiBase
	{
	public:
		UIHUD();
		~UIHUD();
		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;
	private:
		Texture* mTexture;
	};
}