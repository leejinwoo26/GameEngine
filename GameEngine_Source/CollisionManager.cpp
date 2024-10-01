#include "CollisionManager.h"
#include "Scene.h"	
#include "SceneManager.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"


namespace GE
{
	std::bitset < (UINT)eLayerType::MAX> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::MAX] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

	CollisionManager::CollisionManager()
	{
	}
	CollisionManager::~CollisionManager()
	{
	}
	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::MAX; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::MAX; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Render(HDC hdc)
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}
		mCollisionLayerMatrix[row][col] = enable;

	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

		for (GameObject* left: lefts)
		{
			if (left->IsActive() == false)
				continue;
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				if (right->IsActive() == false)
					continue;
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		CollsionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}

	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{ 
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();
		
		if (left->GetState() == Collider::eCollisionState::BOX2D 
			&& right->GetState() == Collider::eCollisionState::BOX2D)
		{
			BoxCollider2D* boxLeft = left->GetOwner()->GetComponent<BoxCollider2D>();
			BoxCollider2D* boxRight = right->GetOwner()->GetComponent<BoxCollider2D>();

			Vector2 leftBoxSize = boxLeft->GetBoxCollsionSize();
			Vector2 RightBoxSize = boxRight->GetBoxCollsionSize();


			Vector2 leftPos = leftTr->GetPosition() + boxLeft->GetOffset();
			Vector2 rightPos = rightTr->GetPosition() + boxRight->GetOffset();

			if (fabs(leftPos.x - rightPos.x) < fabs(leftBoxSize.x / 2.f + RightBoxSize.x / 2.f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftBoxSize.y / 2.f + RightBoxSize.y / 2.f))
			{
				return true;
			}
		}
		else if (left->GetState() == Collider::eCollisionState::CIRCLE2D
			&& right->GetState() == Collider::eCollisionState::CIRCLE2D)
		{
			CircleCollider2D* boxLeft = left->GetOwner()->GetComponent<CircleCollider2D>();
			CircleCollider2D* boxRight = right->GetOwner()->GetComponent<CircleCollider2D>();

			float LeftCircleRad = boxLeft->GetRadius();
			float RightCircleRad = boxRight->GetRadius();

			Vector2 LeftCircleSize = Vector2(LeftCircleRad, LeftCircleRad);
			Vector2 RightCircleSize = Vector2(RightCircleRad, RightCircleRad);

			Vector2 leftPos = leftTr->GetPosition() + boxLeft->GetOffset() + LeftCircleSize;
			Vector2 rightPos = rightTr->GetPosition() + boxRight->GetOffset()+ RightCircleSize;

			float distance = (leftPos - rightPos).length();

			if (distance <= ((LeftCircleRad / 2) + (RightCircleRad / 2)))
			{
				return true;
			}
		}
		else if (left->GetState() == Collider::eCollisionState::BOX2D
			&& right->GetState() == Collider::eCollisionState::CIRCLE2D)
		{
			BoxCollider2D* boxLeft = left->GetOwner()->GetComponent<BoxCollider2D>();
			CircleCollider2D* boxRight = right->GetOwner()->GetComponent<CircleCollider2D>();

			Vector2 LeftBoxSize = boxLeft->GetBoxCollsionSize();
			float RightCircleRad = boxRight->GetRadius();
			float RightCircleRad_Half = RightCircleRad / 2;
			Vector2 RightCircleSize = Vector2(RightCircleRad, RightCircleRad);



			Vector2 leftPos = leftTr->GetPosition() + boxLeft->GetOffset();//³×¸ð
			Vector2 rightPos = rightTr->GetPosition() + boxRight->GetOffset(); //¿ø

			float distance = (leftPos - rightPos).length();

			if (((rightPos.x >= leftPos.x) && (rightPos.x <= leftPos.x + LeftBoxSize.x)))
			{
				if (((rightPos.y >= leftPos.y) && (rightPos.y <= leftPos.y + LeftBoxSize.y)))
				{
					int a = 0;
				}
				else
				{
					int a = 0;
				}
			}

			
		}
		return false;
	}
}