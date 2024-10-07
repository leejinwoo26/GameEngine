#include "AudioClip.h"
namespace GE
{
	AudioClip::AudioClip():
		Resource(eResourceType::AUDIOCLIP),
		mSound(nullptr),
		mChannel(nullptr),
		mMaxDistance(1000),
		mMinDistance(1),
		mbLoop(false)
	{
	}
	AudioClip::~AudioClip()
	{
		mSound->release();
		mSound = nullptr;
	}
	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
		return S_OK;
	}
	void AudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
	}
	void AudioClip::Stop()
	{
		mChannel->stop();
	}
	void AudioClip::Set3DAttributes(const Vector2 pos)
	{
		FMOD_VECTOR fmodPos = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR fmodVel = { 0.0f, 0.0f, 0.0f };

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}