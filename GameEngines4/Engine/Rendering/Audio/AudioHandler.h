#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>
#include <map>
#include <memory>
#include "fmod.hpp"
#include "glm/glm.hpp"
#include "../../Core/Debugger.h"
#include "AudioSource.h"

class AudioHandler
{
public:

	// Singleton 
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();

	bool Initialize(glm::vec3 pos_ = glm::vec3(0.0f), glm::vec3 vel_ = glm::vec3(0.0f),
		glm::vec3 forwardDir = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 upDir_ = glm::vec3(0.0f, 1.0f, 0.0f));

	void OnDestroy();

	void Update(const float deltaTime_);


private:

	AudioHandler();
	~AudioHandler();


	static std::unique_ptr<AudioHandler> audioHandlerInstance;
	friend std::default_delete<AudioHandler>;

	friend class AudioSource;

	// convertes glm vec3 to a fmod vector
	FMOD_VECTOR* glmToFMOD(glm::vec3 vec_);

	// load sound 
	void LoadSound(std::string soundName_, bool shouldLoop_, bool audio3D_, bool audioCompressed_);

	// return a fmod_sound pointer
	FMOD::Sound* GetSound(std::string soundName_);

	// play specific sound returns channelID
	int PlaySound(std::string soundName_, glm::vec3 soundPos_, glm::vec3 soundVel_ = glm::vec3(0.0f), float soundVolume_ = 1.0f);

	//Update position and velocity of a channnel
	void UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_ = glm::vec3(0.0f));

	///See if a specific channel is playing a sound
	bool IsPlaying(int channelID_);

	FMOD::System* fmodSystem;

	static std::map<std::string, FMOD::Sound*>soundPtrMap;

	static std::map<int, FMOD::Channel*>channelPtrMap;

	int channelCount;

	int* driverCount;

	bool shouldLoop;
	bool audio3D;
	bool audioCompressed;

};
#endif