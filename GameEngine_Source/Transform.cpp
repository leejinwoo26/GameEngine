#include "Transform.h"
namespace GE
{
	Transform::Transform() :
		Component(eComponentType::TRANSFORM),
		mScale(Vector2(1.f,1.f)),
		mRotation(0.f)	
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
}