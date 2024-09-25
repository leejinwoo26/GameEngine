#pragma once
namespace GE
{
	enum class eComponentType
	{
		TRANSFORM,
		SPRITERENDERER,
		SCRIPT,
		CAMERA,
		END
	};

	enum class eLayerType
	{
		NONE,
		BACKGROUND,
		PLAYER,
		MAX = 16
	};

	enum class eResourceType
	{
		TEXTURE,
		AUDIOCLIP,
		PREFAB,
		END
	};
}

