#include "pch.h"
#include "Player.h"
namespace GE
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}