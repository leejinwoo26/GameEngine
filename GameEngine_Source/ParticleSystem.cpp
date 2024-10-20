#include "pch.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Object.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Input.h"

extern GE::Application app;

namespace GE
{
	ParticleSystem::ParticleSystem():
		Component(eComponentType::PARTICLESYSTEM)
	{
	}
	ParticleSystem::~ParticleSystem()
	{
	}
	void ParticleSystem::Initialize()
	{
		for (int i = 0; i < 100; i++)
		{
			Particle* particle = new Particle();
			Transform* PS_tr = GetOwner()->GetComponent<Transform>();
			Transform* P_tr = particle->GetComponent<Transform>();
			P_tr->SetPos(PS_tr->GetPosition());

			Particle::Particle_ST pST = {};
			pST.speed = 500;
			float randomX = static_cast<float>(rand() % 2001 - 1000) / 1000.0f; // -10.0 ~ 10.0
			float randomY = static_cast<float>(rand() % 1001 - 500) / 500;   // -5.0 ~ 5.0
			pST.velocity = Vector2(randomX, randomY);
			pST.gravity = Vector2(0, 1);
			particle->SetParticleInfo(pST);
			mParticles.push_back(particle);
		}
	}
	void ParticleSystem::Update()
	{
		if (Input::GetKeyDown(eKeyCode::R))
		{
			for (int i = 0; i < mParticles.size(); i++)
			{
				Particle::Particle_ST p = {};
				Transform* P_tr = mParticles[i]->GetComponent<Transform>();
				P_tr->SetPos(Vector2(800, 500));
				float randomX = static_cast<float>(rand() % 2001 - 1000) / 1000.0f; // -10.0 ~ 10.0
				float randomY = static_cast<float>(rand() % 1001 - 500) / 500;   // -5.0 ~ 5.0
				p.velocity = Vector2(randomX, randomY);
				p.gravity = Vector2(0, 1);
				p.speed = 500;
				mParticles[i]->SetParticleInfo(p);
			}
		}

		for (int i = 0; i < mParticles.size(); i++)
		{
			mParticles[i]->Update();
		}
	}
	void ParticleSystem::LateUpdate()
	{
		for (int i = 0; i < mParticles.size(); i++)
		{
			mParticles[i]->LateUpdate();
		}
	}
	void ParticleSystem::Render(HDC hdc)
	{
		for (int i = 0; i < mParticles.size(); i++)
		{
			mParticles[i]->Render(app.GetParticleBackHdc());
		}
	}

}