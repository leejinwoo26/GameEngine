#pragma once
#include "Component.h"

namespace GE
{
	class ParticleSystem : public Component
	{
	public:
		ParticleSystem();
		~ParticleSystem();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;
	private:
		std::vector<class Particle*> mParticles;
	};
}