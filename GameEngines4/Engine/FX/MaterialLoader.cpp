#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{

}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debugger::Error("Cannot open MTL File: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//add in Ns,d,Ka,Kd,Ks
		if (line.substr(0, 3) == "Ns ") {
			std::stringstream Ns(line.substr(2));
			float shineValue;
			Ns >> shineValue;
			m.shininess = shineValue;
		}

		else if (line.substr(0, 2) == "d ") {
			std::stringstream d(line.substr(2));
			float transparencyValue;
			d >> transparencyValue;
			m.transparency = transparencyValue;
		}

		else if (line.substr(0, 3) == "Ka ") {
			std::stringstream Ka(line.substr(2));
			float x, y, z;
			Ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}

		else if (line.substr(0, 3) == "Kd ") {
			std::stringstream Kd(line.substr(2));
			float x, y, z;
			Kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}

		else if (line.substr(0, 3) == "Ks ") {
			std::stringstream Ks(line.substr(2));
			float x, y, z;
			Ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
