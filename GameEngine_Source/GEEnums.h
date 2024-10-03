#pragma once
namespace GE
{
	enum class eComponentType
	{
		TRANSFORM,
		COLLIDER,
		SPRITERENDERER,
		ANIMATOR,
		SCRIPT,
		CAMERA,
		END
	};

	enum class eLayerType
	{
		NONE,
		BACKGROUND,
		TILE,
		PLAYER,
		ANIMAL,
		PARTICLE,
		MAX = 16
	};

	enum class eResourceType
	{
		TEXTURE,
		AUDIOCLIP,
		ANIMATION,
		PREFAB,
		END
	};
}

