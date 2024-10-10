#pragma once
#include "GameObject.h"

namespace GE
{
	class AnimCut : public GameObject
	{
	public:
		AnimCut();
		~AnimCut();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	public:
		const Vector2& GetOriginPos() const { return originPos; }
		const Vector2& GetSecondPos() const { return secondPos; }
		const Vector2& GetCutSize() const { return CutSize; }
		void SetOriginPos(const Vector2& origin) { originPos = origin; }
		void SetSecondPos(const Vector2& second) { secondPos = second; }
		void SetCutSize(const Vector2& size) { CutSize = size; }

	private:
		Vector2 originPos;
		Vector2 secondPos;
		Vector2 CutSize;
	};
}