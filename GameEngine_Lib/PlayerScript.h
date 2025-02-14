#pragma once
#include "..\\GameEngine_Source\\Script.h"

namespace GE
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			SitDown,
			Walk,
			Sleep,
			Attack,
		};
		PlayerScript();
		~PlayerScript();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void Attack();

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

	private:
		void sitDown();
		void move();

	private:
		eState mState;
		class Animator* mAnimator;
		float mDeathTime;
	};

}