#pragma once
#include "UiBase.h"
#include "Texture.h"

namespace GE
{
	class UIButton : public UiBase
	{
	public:
		UIButton();
		~UIButton();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		virtual void ButtonClick();

	private:
		Texture* mTexture;
		Event mOnClick;
	};
}