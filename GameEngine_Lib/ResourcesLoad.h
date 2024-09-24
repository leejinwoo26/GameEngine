#pragma once
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Texture.h"

namespace GE
{
	void LoadResources()
	{
		Resources::Load<Texture>(L"BG", L"..\\Resource\\CloudOcean.png");
	}
}

