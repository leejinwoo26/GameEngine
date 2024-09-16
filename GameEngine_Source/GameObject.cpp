#include "GameObject.h"

GE::GameObject::GameObject()
{
}

GE::GameObject::~GameObject()
{
}
void GE::GameObject::Initilize()
{
}

void GE::GameObject::Update()
{
}

void GE::GameObject::LateUpdate()
{
}

void GE::GameObject::Render(HDC hdc)
{
	Rectangle(hdc, 300, 300, 400, 400);
}


