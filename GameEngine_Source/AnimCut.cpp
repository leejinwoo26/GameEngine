#include "AnimCut.h"
namespace GE
{
	AnimCut::AnimCut()
	{
	}
	AnimCut::~AnimCut()
	{
	}
	void AnimCut::Initialize()
	{
		GameObject::Initialize();
	}
	void AnimCut::Update()
	{
		GameObject::Update();
		CutSize.x = std::fabsf(secondPos.x - originPos.x);
		CutSize.y = std::fabsf(secondPos.y - originPos.y);
	}
	void AnimCut::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AnimCut::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Rectangle(hdc, originPos.x, originPos.y, secondPos.x, secondPos.y);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}