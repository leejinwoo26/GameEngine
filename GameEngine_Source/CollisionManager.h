#pragma once
#include "CommonInclude.h"

namespace GE
{
	union CollsionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};
	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Clear();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(class Collider* left, class Collider* right);
		static bool Intersect(class Collider* left, class Collider* right);

	private:
		static std::bitset < (UINT)eLayerType::MAX> mCollisionLayerMatrix[(UINT)eLayerType::MAX];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}