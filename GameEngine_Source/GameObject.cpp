#include "GameObject.h"
#include "Input.h"


GE::GameObject::GameObject() 
{
}

GE::GameObject::~GameObject()
{
}
void GE::GameObject::Initilize()
{
	xSpeed = 0;
}

void GE::GameObject::Update()
{
	if (Input::GetKey(eKeyCode::D))
	{
		xSpeed  += 0.1;
	}
}

void GE::GameObject::LateUpdate()
{
}

void GE::GameObject::Render(HDC hdc)
{
	Rectangle(hdc, 300+ xSpeed, 300, 400+ xSpeed, 400);
}


