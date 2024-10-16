#pragma once
namespace GE
{
	enum class eComponentType
	{
		TRANSFORM,
		COLLIDER,
		RIGIDBODY,
		SPRITERENDERER,
		ANIMATOR,
		SCRIPT,
		CAMERA,
		AUDIOLISTENER,
		AUDIOSOURCE,
		PARTICLESYSTEM,
		END
	};

	enum class eLayerType
	{
		NONE,
		CAMERA,
		BACKGROUND,
		TILE,
		PLAYER,
		ANIMATOR,
		ANIMATIONCLIP,
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

	enum class eUIType
	{
		HPBAR,
		BUTTON,
		END
	};
}

