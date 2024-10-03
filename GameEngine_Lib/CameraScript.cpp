#include "CameraScript.h"
#include "..\\GameEngine_Source\\Input.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\Time.h"

namespace GE
{
	CameraScript::CameraScript()
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y -= 1000.f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y += 1000.f * Time::DeltaTime();
		}

		tr->SetPos(pos);
	}
	void CameraScript::LateUpdate()
	{
	}
	void CameraScript::Render(HDC hdc)
	{
	}
	void CameraScript::OnCollisionEnter(Collider* other)
	{
	}
	void CameraScript::OnCollisionStay(Collider* other)
	{
	}
	void CameraScript::OnCollisionExit(Collider* other)
	{
	}
}