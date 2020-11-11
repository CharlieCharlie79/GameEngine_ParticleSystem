#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_)
{
	VAO = 0;
	VBO = 0;

	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;
	colourLocation = 0;

	textureLocation = 0;
	
	textureID = textureID_;

	shaderProgram = shaderProgram_;

	

	lifeTime = 0.0f;
	size = 0.0f;
	angle = 0.0f;
	velocity = glm::vec3(0.0f);
	position = glm::vec3(0.0f);
	colour = glm::vec4(0.0f);
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		
	
	vertexData Plane;
	Plane.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	Plane.textureCoordinates = glm::vec2(0.0f, 0.0f);
	particles.push_back(Plane);	

	Plane.position = glm::vec3(0.5f, 0.5f, 0.0f);
	Plane.textureCoordinates = glm::vec2(1.0f, 0.0f);
	particles.push_back(Plane);

	Plane.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	Plane.textureCoordinates = glm::vec2(0.0f, 1.0f);
	particles.push_back(Plane);

	Plane.position = glm::vec3(0.5f, -0.5f, 0.0f);
	Plane.textureCoordinates = glm::vec2(1.0f, 1.0f);
	particles.push_back(Plane);

	GenerateBuffers();
}
Particle::~Particle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	

	/*if (subMesh.vertextList.size() > 0) {
		subMesh.vertextList.clear();
	}*/

	//if (subMesh.meshIndices.size() > 0) {
	//	subMesh.meshIndices.clear();
	//}
}
glm::mat4 Particle::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	return model;
}


void Particle::Render(Camera* camera_) 
{
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::vec4 getDistance = camera_->GetView() * GetTransform(position, angle, rotation, glm::vec3(size)) * glm::vec4(position, 1.0f);
	float distance = getDistance.xyz().length();
	float attenuation = 1.0f / sqrt(0.1f * distance);


	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GetTransform(position, angle, rotation, glm::vec3(size * attenuation))));

	glUniform4f(colourLocation, colour.x, colour.y, colour.z, colour.w);
	glUniform1ui(textureLocation, 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, particles.size());

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

void Particle::GenerateBuffers()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(vertexData), &particles[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (GLvoid*)offsetof(vertexData, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (GLvoid*)offsetof(vertexData, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "proj");
	colourLocation = glGetUniformLocation(shaderProgram, "colour");
	textureLocation = glGetUniformLocation(shaderProgram, "textureID");

	
}