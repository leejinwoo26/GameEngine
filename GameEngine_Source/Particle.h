#pragma once
#include "GameObject.h"

namespace GE
{
	class Particle : public GameObject
	{
	public:
		struct Particle_ST
		{
			Vector2 velocity;
			float speed;
			Vector2 gravity;
		};

		Particle();
		~Particle();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;
		Particle_ST& GetParticleInfo() { return mParticleInfo; }
		void SetParticleInfo(Particle_ST& info) { mParticleInfo = info; }
	private:
		Particle_ST mParticleInfo;
	};
}