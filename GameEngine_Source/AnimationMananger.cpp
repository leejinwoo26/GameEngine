#include "pch.h"
#include "AnimationMananger.h"
#include "Texture.h"
#include "Animation.h"

namespace GE
{
	std::unordered_map<std::wstring, std::vector<AnimationMananger::AnimInfo>> AnimationMananger::animSprites = {};

	void AnimationMananger::Initialize()
	{
		std::vector<AnimInfo> idle_RightInfo =
		{
			{ {0.0f, 0.0f}, {36, 77} , {1,1} },
			{ {74.0f, 0.0f}, {36.0f, 78.0f} , {0,0} },
			{ {148.0f, 0.0f}, {36.0f, 79.0f} , {0,0} },
			{ {74.0f, 0.0f}, {36.0f, 78.0f} , {0,0} },
		};
		animSprites[L"Idle_Right"].insert(animSprites[L"Idle_Right"].end(), idle_RightInfo.begin(), idle_RightInfo.end());
		std::vector<AnimInfo> Walk_RightInfo =
		{
			{ {222.0f, 0.0f}, {40, 76} , {4,0} },
			{ {296.0f, 0.0f}, {32.0f, 77.0f} , {0,0} },
			{ {370.0f, 0.0f}, {32.0f, 77.0f} , {0,0} },
			{ {444.0f, 0.0f}, {36.0f, 76.0f} , {2,0} },
			{ {518.0f, 0.0f}, {32.0f, 77.0f} , {0,0} },
			{ {592.0f, 0.0f}, {32.0f, 77.0f} , {0,0} },
		};
		animSprites[L"Walk_Right"].insert(animSprites[L"Walk_Right"].end(), Walk_RightInfo.begin(), Walk_RightInfo.end());

		std::vector<AnimInfo> Run_RightInfo =
		{
			{ {666.0f, 0.0f}, {56, 58} , {0,0} },
			{ {740.0f, 0.0f}, {48.0f, 59.0f} , {2,0} },
			{ {814.0f, 0.0f}, {54.0f, 63.0f} , {0,3} },
		};
		animSprites[L"Run_Right"].insert(animSprites[L"Run_Right"].end(), Run_RightInfo.begin(), Run_RightInfo.end());

		std::vector<AnimInfo> Flying_Right_RFoot_Info =
		{
			{ {888.0f, 0.0f}, {34, 75} , {0,0} },
			{ {962.0f, 0.0f}, {38.0f, 73.0f} , {2,-1.5} },
		};
		animSprites[L"Flying_Right"].insert(animSprites[L"Flying_Right"].end()
			, Flying_Right_RFoot_Info.begin(), Flying_Right_RFoot_Info.end());

		std::vector<AnimInfo> Land_RightInfo =
		{
			{ {1036.0f, 0.0f}, {46, 59} , {0,0} },
		};
		animSprites[L"Land_Right"].insert(animSprites[L"Land_Right"].end(), Land_RightInfo.begin(), Land_RightInfo.end());

		std::vector<AnimInfo> jump_RightInfo =
		{
			{ {1100.0f, 0.0f}, {50, 75} , {0,0} },
		};
		animSprites[L"Jump_Right"].insert(animSprites[L"Jump_Right"].end(), jump_RightInfo.begin(), jump_RightInfo.end());

		std::vector<AnimInfo> A_Idle_RightInfo =
		{
			{ {1184.0f, 0.0f}, {46, 69} , {0,1} },
			{ {1258.0f, 0.0f}, {46.0f, 70.0f} , {0,0} },
			{ {1332.0f, 0.0f}, {46.0f, 71.0f} , {0,0} },
			{ {1258.0f, 0.0f}, {46.0f, 70.0f} , {0,0} },
		};
		animSprites[L"A_Idle_Right"].insert(animSprites[L"A_Idle_Right"].end(), A_Idle_RightInfo.begin(), A_Idle_RightInfo.end());

		std::vector<AnimInfo> N_Attack_H_RightInfo =
		{
			{ {1480.0f, 0.0f}, {46, 72} , {0,-1} },
			{ {1554.0f, 0.0f}, {46.0f, 70.0f} , {0,0} },
			{ {1627.0f, 0.0f}, {46.0f, 69.0f} , {-1,1} },
			{ {1702.0f, 0.0f}, {46.0f, 69.0f} , {0,1} },
			{ {1776.0f, 0.0f}, {46.0f, 69.0f} , {0,1} },
		};
		animSprites[L"N_Attack_H_Right"].insert(animSprites[L"N_Attack_H_Right"].end(),\
			N_Attack_H_RightInfo.begin(), N_Attack_H_RightInfo.end());

		std::vector<AnimInfo> N_Attack_V_RightInfo =
		{
			{ {1850.0f, 0.0f}, {42, 76} , {0,-2} },
			{ {1924.0f, 0.0f}, {42, 75} , {0,0} },
			{ {1998.0f, 0.0f}, {48, 69} , {-2,2} },
			{ {2072.0f, 0.0f}, {46, 69} , {-3,2} },
			{ {2072.0f, 0.0f}, {46, 69} , {-3,2} },
		};
		animSprites[L"N_Attack_V_Right"].insert(animSprites[L"N_Attack_V_Right"].end(), N_Attack_V_RightInfo.begin(), N_Attack_V_RightInfo.end());

		std::vector<AnimInfo> N_Attack_St_RightInfo =
		{
			{ {2146.0f, 0.0f}, {44, 76} , {0,-4} },
			{ {2220.0f, 0.0f}, {46, 69} , {0,0} },
			{ {2294.0f, 0.0f}, {48, 69} , {1,0} },
			{ {2368.0f, 0.0f}, {48, 69} , {1,0} },
		};
		animSprites[L"N_Attack_St_Right"].insert(animSprites[L"N_Attack_St_Right"].end(), N_Attack_St_RightInfo.begin(), N_Attack_St_RightInfo.end());

		std::vector<AnimInfo> Defence_RightInfo =
		{
			{ {2442.0f, 0.0f}, {52, 69} , {0,0} },
		};
		animSprites[L"Defence_Right"].insert(animSprites[L"Defence_Right"].end(), Defence_RightInfo.begin(), Defence_RightInfo.end());

		std::vector<AnimInfo> hitted_RightInfo =
		{
			{ {2516.0f, 0.0f}, {44, 76} , {0,0} },
		};
		animSprites[L"Hitted_Right"].insert(animSprites[L"Hitted_Right"].end(), hitted_RightInfo.begin(), hitted_RightInfo.end());

		std::vector<AnimInfo> HandStorm_RightInfo =
		{
			{ {2590.0f, 0.0f}, {42, 77} , {0,1} },
			{ {2664.0f, 0.0f}, {42, 78} , {-1,0} },
			{ {2738.0f, 0.0f}, {42, 79} , {-1,0} },
			{ {2812.0f, 0.0f}, {40, 78} , {-2,0} },
			{ {2886.0f, 0.0f}, {52, 69} , {5,6} },
		};
		animSprites[L"HandStorm_Right"].insert(animSprites[L"HandStorm_Right"].end(), HandStorm_RightInfo.begin(), HandStorm_RightInfo.end());

		std::vector<AnimInfo> EnergCharge_RightInfo =
		{
			{ {2960.0f, 0.0f}, {36, 77} , {0,0} },
			{ {3034.0f, 0.0f}, {36, 78} , {-1,-1} },
			{ {3108.0f, 0.0f}, {36, 79} , {-1,-1} },
		};
		animSprites[L"EnergCharge_Right"].insert(animSprites[L"EnergCharge_Right"].end(),
			EnergCharge_RightInfo.begin(), EnergCharge_RightInfo.end());

		std::vector<AnimInfo> Breathing_RightInfo =
		{
			{ {3182.0f, 0.0f}, {34, 68} , {0,0} },
		};
		animSprites[L"Breathing_Right"].insert(animSprites[L"Breathing_Right"].end(), Breathing_RightInfo.begin(), Breathing_RightInfo.end());

		std::vector<AnimInfo> Dead_RightInfo =
		{
			{ {3256.0f, 0.0f}, {44, 47} , {0,0} },
			{ {3330.0f, 0.0f}, {74, 36} , {0,3} },
		};
		animSprites[L"Dead_Right"].insert(animSprites[L"Dead_Right"].end(), Dead_RightInfo.begin(), Dead_RightInfo.end());

		std::vector<AnimInfo> Anger_RightInfo =
		{
			{ {3404.0f, 0.0f}, {46, 70} , {0,0} },
			{ {3478.0f, 0.0f}, {46, 70} , {0,0} },
		};
		animSprites[L"Anger_Right"].insert(animSprites[L"Anger_Right"].end(), Anger_RightInfo.begin(), Anger_RightInfo.end());

		std::vector<AnimInfo> cloth_Info =
		{
			{ {0, 0}, {42, 50} , {0,0} },
			{ {42, 0}, {42, 50} , {0,0} },
			{ {84, 0}, {42, 52} , {0,2} },
			{ {42, 0}, {42, 50} , {0,0} }
		};
		animSprites[L"cloth"].insert(animSprites[L"cloth"].end(), cloth_Info.begin(), cloth_Info.end());

	}
	
}