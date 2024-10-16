#include "pch.h"
#include "Particle.h"
#include "GETime.h"
#include "..\\GameEngine_Lib\\ParticleScene.h"
#include "Application.h"

extern GE::Application app;

namespace GE
{
	Particle::Particle()  
	{
		GameObject::SetLayerType(eLayerType::PARTICLE);
		particleInfo.color = BLACK;
		particleInfo.duration = 3.0f;
		particleInfo.lifetime = 2.0f;
		particleInfo.Looping = true;
		particleInfo.size = Vector2(20,20);
		particleInfo.direction = Vector2(0,10);
		particleInfo.speed = 10.f;
		particleInfo.startPos = Vector2(500, 350);
	}
	Particle::~Particle()
	{
	}
	void Particle::Initialize()
	{
	}
	void Particle::Update()
	{
		y -= 100.f * Time::DeltaTime();
	}
	void Particle::LateUpdate()
	{
	}
	void Particle::Render(HDC hdc)
	{
		HDC backDc = app.GetParticleBackHdc();
		Ellipse(backDc
			, particleInfo.startPos.x
			, particleInfo.startPos.y + y
			, particleInfo.startPos.x + particleInfo.size.x
			, particleInfo.startPos.y + particleInfo.size.y + y);
	}
}