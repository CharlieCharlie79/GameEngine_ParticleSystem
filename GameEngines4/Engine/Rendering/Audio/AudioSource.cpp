#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(std::string soundName_, bool shouldLoop, bool audio3D_, bool audioCompressed_)
{
	channelID = -1;

	soundName = soundName_;

	AudioHandler::GetInstance()->LoadSound(soundName, shouldLoop, audio3D_, audioCompressed_);
}

AudioSource::~AudioSource()
{

}

bool AudioSource::OnCreate(GameObject* gameObject_)
{
	parent = gameObject_;
	PlaySound();
	std::cout << ("AudioSource has been created\n");
	return true;
}

void AudioSource::Update(const float deltaTime_)
{
	AudioHandler::GetInstance()->Update(deltaTime_);
}

void AudioSource::PlaySound()
{
	channelID = AudioHandler::GetInstance()->PlaySound(soundName, parent->GetPosition());
}

bool AudioSource::isPlaying()
{
	return AudioHandler::GetInstance()->IsPlaying(channelID);
}