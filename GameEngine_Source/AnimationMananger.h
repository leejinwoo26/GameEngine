#pragma once
#include "CommonInclude.h"

namespace GE
{
	class AnimationMananger
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 Size;
			Vector2 Offset;
			float duration;

			Sprite() :
				leftTop(Vector2(0.f, 0.f)),
				Size(Vector2(0.f, 0.f)),
				Offset(Vector2(0.f, 0.f)),
				duration(0.f)
			{
			}
		};
		struct AnimInfo
		{
			Vector2 LeftTop;
			Vector2 SpriteSize;
			Vector2 Offset;
		};
		AnimationMananger();
		~AnimationMananger();

		static void Initialize();

		static const std::unordered_map<std::wstring, std::vector<AnimInfo>>& GetAnimSprites() { return animSprites; }
	private:
		static std::unordered_map<std::wstring, std::vector<AnimInfo>> animSprites;
	};
}