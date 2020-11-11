#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int NumberOfParticles_, std::string textureID_, std::string ShaderProgram_)
{
	particles.reserve(NumberOfParticles_);
	NumberOfParticles = NumberOfParticles_;
	
	TextureHandler::GetInstance()->CreateTexture(textureID_, "./Resources/Textures/" + textureID_);
	textureID = TextureHandler::GetInstance()->GetTexture(textureID_);
	shaderID = ShaderHandler::GetInstance()->GetShader(ShaderProgram_);
	CreateParticles();
	
}

ParticleEmitter::~ParticleEmitter()
{
	if (particles.size() > 0)
	{
		for (auto m : particles)
		{
			delete m;
			m = nullptr;
		}
		particles.clear();
	}
}


void ParticleEmitter::CreateParticles()
{
	if (textureID == 0)
	{
		Debugger::Error("Could not create, textureID is equal to 0", "ParticleEmitter.cpp", __LINE__);
		return;
	}

	if (shaderID == 0)
	{
		Debugger::Error("Could not create, shaderID is equal to 0", "ParticleEmitter.cpp", __LINE__);
		return;
	}


	for (float i = 0; i < NumberOfParticles; i++)
	{
		Particle* particle = new Particle(shaderID, textureID);
		randomParticle(particle);
		particles.push_back(particle);		
	}
	
	
}

void ParticleEmitter::randomParticle(Particle *particle)
{	
	particle->size = 0.1f;
	particle->lifeTime = 1.0f;
	particle->position = glm::vec3(0.0f);
	particle->velocity = glm::vec3(std::rand() % 5, std::rand() % 5, std::rand() % 5);
	particle->colour = glm::vec4(1.5f, 1.5f, 1.5f, 1.0f);	
}


void ParticleEmitter::renderEmitter(Camera *camera)
{
	if (particles.size() > 0)
	{
		glUseProgram(shaderID);
		for (auto P : particles)
		{
			P->Render(camera);
		}
	}

}

void ParticleEmitter::Update(float deltaTime)
{
	if (particles.size() > 0)
	{
		for (auto p : particles)
		{
			p->lifeTime = p->lifeTime - deltaTime;

			if (p->lifeTime <= 0.0f) {
				randomParticle(p);
			}

			p->position = p->position + (p->velocity * deltaTime);
		}
	}
}
