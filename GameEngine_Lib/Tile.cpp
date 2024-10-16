#include "pch.h"
#include "Tile.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\Component.h"
#include "TileRenderer.h"


namespace GE
{
	Tile::Tile()
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::Initialize()
	{
		GameObject::Initialize();
	}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Tile::SetIndexPos(int x, int y)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(x * TileRenderer::GetTileSize().x, y * TileRenderer::GetTileSize().y));
	}
}