#pragma once
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Texture.h"

namespace GE
{
	void LoadResources()
	{
		Resources::Load<Texture>(L"Idle", L"..\\Resource\\Idle.png");
		Resources::Load<Texture>(L"Run", L"..\\Resource\\Run.png");
		Resources::Load<Texture>(L"Hit", L"..\\Resource\\Hit.png");
		Resources::Load<Texture>(L"Aim", L"..\\Resource\\Aim.png");
		Resources::Load<Texture>(L"Dash", L"..\\Resource\\Dash.png");
		Resources::Load<Texture>(L"Death", L"..\\Resource\\Death.png");
		Resources::Load<Texture>(L"Shoot", L"..\\Resource\\Shoot.png");
		Resources::Load<Texture>(L"SpecialAttack_Air", L"..\\Resource\\SpecialAttack_Air.png");
		Resources::Load<Texture>(L"SpecialAttack_Ground", L"..\\Resource\\SpecialAttack_Ground.png");
		Resources::Load<Texture>(L"SuperBeam_SFX", L"..\\Resource\\SuperBeam_SFX.png");
		Resources::Load<Texture>(L"Dust", L"..\\Resource\\Dust.png");
		Resources::Load<Texture>(L"Jump", L"..\\Resource\\Jump.png");
		Resources::Load<Texture>(L"Duck", L"..\\Resource\\Duck.png");
		Resources::Load<Texture>(L"Parry_Axe", L"..\\Resource\\Parry_Axe.png");
		Resources::Load<Texture>(L"Parry_Hand", L"..\\Resource\\Parry_Hand.png");
		Resources::Load<Texture>(L"PeaShooter", L"..\\Resource\\peaShooter.png");
		Resources::Load<Texture>(L"SpringFloor", L"..\\Resource\\SpringFloor.bmp");
	}
}

