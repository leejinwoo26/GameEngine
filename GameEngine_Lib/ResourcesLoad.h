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
		Resources::Load<Texture>(L"Boy_Right", L"..\\Resource\\Boy_Right.bmp");
		Resources::Load<Texture>(L"Boy_Left", L"..\\Resource\\Boy_Left.bmp");
		Resources::Load<Texture>(L"Boy_Right_32", L"..\\Resource\\Boy_Right_32.bmp");
		Resources::Load<Texture>(L"whiteHair", L"..\\Resource\\whiteHair.bmp");
		Resources::Load<Texture>(L"cloth", L"..\\Resource\\cloth.bmp");
	}
}

