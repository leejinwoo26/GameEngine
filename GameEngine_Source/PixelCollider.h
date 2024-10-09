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
		bool isCollisionPixel(ePixelColDirection direction) { return mPixelCollsions[(UINT)direction];}
	private:
		std::bitset<(UINT)ePixelColDirection::NONE + 1> mPixelCollsions;
		class Texture* mPixelMap;
	};
}