#include "Fmod.h"
namespace GE
{
	FMOD::Studio::System* Fmod::mSystem = nullptr;
	FMOD::System* Fmod::mCoreSystem = nullptr;

	void Fmod::Initialize()
	{
		void* extraDriverData = nullptr;

		FMOD::Studio::System::create(&mSystem);

		mSystem->getCoreSystem(&mCoreSystem);
		mCoreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
	}
}