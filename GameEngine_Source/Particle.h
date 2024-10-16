#pragma once
#include "CommonInclude.h"
#include "GameObject.h"

namespace GE
{
	class Particle : public GameObject
	{
	public:
		struct Particle_Struct
		{
			Vector2 startPos;
			Vector2 direction;
			Vector2 size;

			float speed;
			float duration;
			float lifetime;
			bool Looping;

			COLORREF color;
		};

		Particle();
		~Particle();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	private:
		Particle_Struct particleInfo;
		int y;
	};
}