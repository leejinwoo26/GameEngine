#pragma once
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Texture.h"

namespace GE
{
	void LoadResources()
	{
		Resources::Load<Texture>(L"BG", L"..\\Resource\\CloudOcean.png");
		Resources::Load<Texture>(L"Cat", L"..\\Resource\\ChickenAlpha.bmp");
		Resources::Load<Texture>(L"SpringFloor", L"..\\Resource\\SpringFloor.bmp");
		Resources::Load<Texture>(L"HPBAR", L"..\\Resource\\HPBAR.bmp");
		Resources::Load<Texture>(L"PixelMap", L"..\\Resource\\PixelMap.bmp");
	}
}

