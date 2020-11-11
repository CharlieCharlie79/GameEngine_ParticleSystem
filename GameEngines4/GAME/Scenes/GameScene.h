#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "../Test Cases/ComponentA.h"
#include "../Test Cases/ComponentB.h"
#include "../Test Cases/ComponentC.h"
#include"../../Engine/Rendering/Particles/Particle.h"
#include "../../Engine/Rendering/Particles/ParticleEmitter.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	LightSource* lightSource; 
	ParticleEmitter* particleEmitter;

	
};
#endif

