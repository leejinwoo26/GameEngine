#include "CameraScript.h"
#include "..\\GameEngine_Source\\Input.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\GETime.h"
#include "..\\GameEngine_Source\\Debug_Text.h"

namespace GE
{
	CameraScript::CameraScript() : mSpeed(500)
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
			pos.x += mSpeed* Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mSpeed += 100.f;
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			mSpeed -= 100.f;
		}
		

		tr->SetPos(pos);
	}
	void CameraScript::LateUpdate()
	{
	}
	void CameraScript::Render(HDC hdc)
	{
		//디버그 나중에 삭제
		Print_Text(hdc, L"Speed", mSpeed, Vector2(1400, 600));
		Print_Text(hdc, L"스피드업 : Q " ,Vector2(1400, 650));
		Print_Text(hdc, L"스피드다운 : W ", Vector2(1400, 700));
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