#pragma once
#include "Component.h"

namespace GE
{
	class Collider : public Component
	{
	public:
		enum class eCollisionState
		{
			NONE,
			BOX2D,
			CIRCLE2D,
			Pixel2D
		};

		Collider();
		~Collider();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		UINT32 GetID() { return mID; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }

		eCollisionState GetState() { return mState; }
		void SetState(eCollisionState state) { mState = state; }

	private:
		static UINT32 mCollisionID;
		UINT32 mID;
		Vector2 mOffset;
		Vector2 mSize;
		eCollisionState mState;
	};
}
