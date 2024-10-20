#include "pch.h"
#include "Particle.h"
#include "Debug_Text.h"
#include "Application.h"
#include "Object.h"
#include "GameObject.h"
#include "Transform.h"
#include "GETime.h"
#include "Debug_Text.h"

extern GE::Application app;

namespace GE
{
	Particle::Particle()
	{
		mParticleInfo.speed = 10.f;
		mParticleInfo.velocity = Vector2(0, 1);
		mParticleInfo.gravity = Vector2(0, 1);
	}
	Particle::~Particle()
	{
	}
	void Particle::Initialize()
	{
	}
	void Particle::Update()
	{
		Transform* tr = this->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		pos += mParticleInfo.velocity * mParticleInfo.speed * Time::DeltaTime();
		mParticleInfo.velocity += mParticleInfo.gravity * Time::DeltaTime();;


		tr->SetPos(pos);
	}
	void Particle::LateUpdate()
	{
	}
	void Particle::Render(HDC hdc)
	{
		HDC back = app.GetParticleBackHdc();
		Transform* tr = this->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Ellipse(back,
			pos.x + 100,
			pos.y + 100,
			pos.x + 125,
			pos.y + 125 );
	}
}