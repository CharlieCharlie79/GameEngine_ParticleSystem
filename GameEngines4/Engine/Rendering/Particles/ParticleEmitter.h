#ifndef ParticleEmitter_H
#define ParticleEmitter_H

#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include "../../Core/Debugger.h"
#include "Particle.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Graphics/ShaderHandler.h"



class ParticleEmitter
{	
public:
	ParticleEmitter(int NumberOfParticles_, std::string textureID_, std::string ShaderProgram_);
	~ParticleEmitter();
	
	std::vector<Particle*>particles;
	
	 int NumberOfParticles;

	 int textureID;

	 int shaderID;

	glm::vec3 position;
	
	time_t timer; 

	
	void CreateParticles();

	void randomParticle(Particle *particle);

	void Update(float deltaTime);

	void renderEmitter(Camera *camera);
};




#endif // !ParticleEmitter