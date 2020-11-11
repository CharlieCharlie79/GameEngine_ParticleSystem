#ifndef PARTICLE_H
#define PARTICLE_H
#define GLM_SWIZZLE

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include <../../OpenGL/include/glm/glm.hpp>
#include "../../Graphics/MaterialHandler.h"



struct vertexData
{
	glm::vec3 position;
	
	glm::vec2 textureCoordinates;
	
	glm::vec4 gl_Position;
	/*float gl_PointSize;
	float gl_ClipDistance[];*/
};


//This class is similar to the Mesh class and SpriteSurface class
class Particle
{
public:
	Particle(GLuint shaderProgram_, GLuint textureID_);
	~Particle();

	void Render(Camera* camera_);

	float lifeTime;
	float size;
	float angle;
	
	///
	//int Nparticle;
	///

	glm::vec3 velocity;
	glm::vec4 colour;
	glm::vec3 position;
	glm::vec3 rotation;


private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	GLuint textureID;
	
	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint colourLocation, textureLocation;
	
	std::vector<vertexData> particles;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)const;
	

};

#endif // !PARTICLE_H