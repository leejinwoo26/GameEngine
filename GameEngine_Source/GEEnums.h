#pragma once
namespace GE
{
	enum class eComponentType
	{
		TRANSFORM,
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
		PLAYER,
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

