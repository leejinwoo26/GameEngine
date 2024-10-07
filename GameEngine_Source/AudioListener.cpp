#include "AudioListener.h"
#include "Transform.h"
#include "GameObject.h"
#include "Fmod.h"



namespace GE
{
	AudioListener::AudioListener():
		Component(eComponentType::AUDIOLISTENER)
	{
	}
	AudioListener::~AudioListener()
	{
	}
	void AudioListener::Initialize()
	{
	}
	void AudioListener::Update()
	{
	}
	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Fmod::Set3DListenerAttributes(&pos);
	}
	void AudioListener::Render(HDC hdc)
	{
	}
}