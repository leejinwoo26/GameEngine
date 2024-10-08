#pragma once
#include "Collider.h"

namespace GE
{
	class PixelCollider : public Collider
	{
	public:
		enum class ePixelColDirection
		{
			LEFT,
			RIGHT,
			UP,
			DOWN,
			NONE
		};

		PixelCollider();
		~PixelCollider();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void PixelUpdate();
		class Texture* GetPixelMap() { return mPixelMap;}
		void SetPixelMap(class Texture* pixelMap) {mPixelMap = pixelMap;}
		bool isCollisionPixel_Up() { return mPixelCollsions[(UINT)ePixelColDirection::UP];}
		bool isCollisionPixel_Down() { return mPixelCollsions[(UINT)ePixelColDirection::DOWN];}
		bool isCollisionPixel_Left() { return mPixelCollsions[(UINT)ePixelColDirection::LEFT];}
		bool isCollisionPixel_Right() { return mPixelCollsions[(UINT)ePixelColDirection::RIGHT];}
	private:
		std::bitset<(UINT)ePixelColDirection::NONE + 1> mPixelCollsions;
		class Texture* mPixelMap;
	};
}