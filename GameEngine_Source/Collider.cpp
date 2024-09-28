#include "Collider.h"
namespace GE
{
	Collider::Collider(): 
		Component(eComponentType::COLLIDER),
		mOffset(Vector2(0.f,0.f))
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::LateUpdate()
	{
	}
	void Collider::Render(HDC hdc)
	{
	}
}