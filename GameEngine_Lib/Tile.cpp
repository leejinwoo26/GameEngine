#include "Tile.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\Transform.h"

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
}