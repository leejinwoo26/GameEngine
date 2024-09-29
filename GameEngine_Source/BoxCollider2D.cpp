#include "BoxCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"

namespace GE
{
	BoxCollider2D::BoxCollider2D() : 
		Collider(), 
		mBoxCollisionSize(Vector2::One)
	{
	}
	BoxCollider2D::~BoxCollider2D()
	{
	}
	void BoxCollider2D::Initialize()
	{
		Collider::SetState(Collider::eCollisionState::BOX);
	}
	void BoxCollider2D::Update()
	{
	}
	void BoxCollider2D::LateUpdate()
	{
	}
	void BoxCollider2D::Render(HDC hdc)
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

		Rectangle(hdc, pos.x + offset.x - (mBoxCollisionSize.x/2.f),
			pos.y + offset.y - (mBoxCollisionSize.y/2.f),
			pos.x + offset.x + (mBoxCollisionSize.x / 2.f),
			pos.y + offset.y + (mBoxCollisionSize.y / 2.f));

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}