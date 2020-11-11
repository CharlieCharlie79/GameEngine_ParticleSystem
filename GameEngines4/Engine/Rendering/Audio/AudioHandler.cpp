#include "AudioHandler.h"

std::map<int, FMOD::Channel*>AudioHandler::channelPtrMap = std::map<int, FMOD::Channel*>();
std::map<std::string, FMOD::Sound*>AudioHandler::soundPtrMap = std::map<std::string, FMOD::Sound*>();

std::unique_ptr<AudioHandler> AudioHandler::audioHandlerInstance = nullptr;

AudioHandler* AudioHandler::GetInstance()
{
	if (audioHandlerInstance.get() == nullptr)
	{
		audioHandlerInstance.reset(new AudioHandler());
	}
	return audioHandlerInstance.get();
}

bool AudioHandler::Initialize(glm::vec3 pos_, glm::vec3 vel_, glm::vec3 forwardDir, glm::vec3 upDir_)
{
	channelCount = -1;

	FMOD::System_Create(&fmodSystem);

	if (FMOD::System_Create(&fmodSystem) != FMOD_OK)
	{
		Debugger::Error("Failed to Initialze FMOD!", "AudioHandler.cpp", __LINE__);
		return false;
	}

	if (fmodSystem->getNumDrivers(driverCount) <= 0)
	{
		Debugger::Error("There are ", "AudioHandler.cpp", __LINE__);
	}

	fmodSystem->init(2, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);

	fmodSystem->set3DListenerAttributes(0, glmToFMOD(pos_), glmToFMOD(vel_), glmToFMOD(forwardDir), glmToFMOD(upDir_));

	return true;
}

void AudioHandler::OnDestroy()
{
	for (auto snd : soundPtrMap)
	{
		FMOD_Sound_Release(reinterpret_cast<FMOD_SOUND*>(&soundPtrMap));
		snd.second = nullptr;
	}
	soundPtrMap.clear();

	for (auto channel : channelPtrMap)
	{
		FMOD_Channel_Stop(reinterpret_cast<FMOD_CHANNEL*>(&channelPtrMap));
		channel.second = nullptr;
	}
	channelPtrMap.clear();

	fmodSystem->close();
	fmodSystem->release();
	fmodSystem = nullptr;
}

void AudioHandler::Update(const float deltaTime_)
{
	fmodSystem->update();
}

AudioHandler::AudioHandler()
{

}

AudioHandler::~AudioHandler()
{
	OnDestroy();
}

FMOD_VECTOR* AudioHandler::glmToFMOD(glm::vec3 vec_)
{
	FMOD_VECTOR* fmodVec = new FMOD_VECTOR;

	fmodVec->x = vec_.x;
	fmodVec->y = vec_.y;
	fmodVec->z = vec_.z;

	return fmodVec;
}

void AudioHandler::LoadSound(std::string soundName_, bool shouldLoop_, bool audio3D_, bool audioCompressed_)
{
	bool shouldLoop = shouldLoop_;
	bool audio3D = audio3D_;
	bool audioCompressed = audioCompressed_;

	if (GetSound(soundName_) != nullptr)
	{
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;

	if (shouldLoop_)
	{
		mode = mode | FMOD_LOOP_NORMAL;
	}
	else
	{
		mode = mode | FMOD_LOOP_OFF;
	}

	if (audio3D_)
	{
		mode = mode | FMOD_3D;
	}
	else
	{
		mode = mode | FMOD_2D;
	}

	if (audioCompressed_)
	{
		mode = mode | FMOD_CREATESTREAM;
	}
	else
	{
		mode = mode | FMOD_CREATESAMPLE;
	}

	FMOD::Sound* soundPtr = nullptr;

	std::string tempString = "./Resources/Audio/" + soundName_;

	fmodSystem->createSound(tempString.c_str(), mode, nullptr, &soundPtr);

	soundPtrMap.insert(std::pair<std::string, FMOD::Sound*>(soundName_, soundPtr));
}

FMOD::Sound* AudioHandler::GetSound(std::string soundName_)
{
	if (soundPtrMap.find(soundName_) != soundPtrMap.end())
	{
		return soundPtrMap[soundName_];
	}
	else
	{
		return nullptr;
	}
}

int AudioHandler::PlaySound(std::string soundName_, glm::vec3 soundPos_, glm::vec3 soundVel_, float soundVolume_)
{
	if (GetSound(soundName_) == nullptr)
	{
		LoadSound(soundName_, shouldLoop, audio3D, audioCompressed);
	}

	int channelID = -1;

	FMOD::Channel* channelPtr = nullptr;

	fmodSystem->playSound(GetSound(soundName_), nullptr, true, &channelPtr);

	channelPtr->set3DAttributes(glmToFMOD(soundPos_), glmToFMOD(soundVel_));

	channelPtr->setVolume(soundVolume_);

	channelPtr->setPaused(false);

	channelID = channelID + 1;

	channelPtrMap.insert(std::pair<int, FMOD::Channel*>(channelID, channelPtr));

	return channelID;
}

void AudioHandler::UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_)
{
	if (channelPtrMap.find(channelID_) != channelPtrMap.end())
	{
		fmodSystem->set3DListenerAttributes(0, glmToFMOD(newPos_), glmToFMOD(newVel_), nullptr, nullptr);
	}
}

bool AudioHandler::IsPlaying(int channelID_)
{
	bool audioPlaying;

	if (channelPtrMap.count(channelID_))
	{
		audioPlaying = IsPlaying(channelID_);
	}

	return audioPlaying;
}

