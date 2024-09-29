#include "Collider.h"
#include "Script.h"
#include "GameObject.h"

namespace GE
{
	UINT32 Collider::mCollisionID = 1;
	Collider::Collider() :
		Component(eComponentType::COLLIDER),
		mOffset(Vector2(0.f, 0.f)),
		mID(mCollisionID++),
		mSize(Vector2::One),
		mState(Collider::eCollisionState::NONE)
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
	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr)
			return;
		script->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr)
			return;
		script->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr)
			return;
		script->OnCollisionExit(other);
	}
}