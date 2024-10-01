#include "CircleCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"


namespace GE
{
	CircleCollider2D::CircleCollider2D():
		mRadius(0)
	{
	}
	CircleCollider2D::~CircleCollider2D()
	{
	}
	void CircleCollider2D::Initialize()
	{
		Collider::SetState(eCollisionState::CIRCLE2D);
	}
	void CircleCollider2D::Update()
	{
	}
	void CircleCollider2D::LateUpdate()
	{
	}
	void CircleCollider2D::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Vector2 offset = GetOffset();

		if (mainCamera->GetTarget())
		{
			pos = mainCamera->CalculatePosition(pos);
		}

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Ellipse(hdc, pos.x + offset.x - (mRadius / 2),
			pos.y + offset.y - (mRadius / 2),
			pos.x + offset.x + (mRadius / 2),
			pos.y + offset.y + (mRadius / 2));

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}