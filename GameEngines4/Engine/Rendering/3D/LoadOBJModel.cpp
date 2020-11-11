#include "LoadOBJModel.h"
#include <sstream>
#include <algorithm>

LoadOBJModel::LoadOBJModel() {
	currentMaterial = Material();
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	OnDestroy(); 
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_); 
	LoadModel(objFilePath_);
}

void LoadOBJModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	
	if (!in) {
		Debugger::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return; 
	}

	float tempnum = 0;

	std::string line; 
	while (std::getline(in, line)) {

		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			
			vertices.push_back(glm::vec3(x, y, z));

			if (tempnum == 0) {
				box.maxVert.x = box.minVert.x = x;
				box.maxVert.x = box.minVert.y = y;
				box.maxVert.x = box.minVert.z = z;
			}

			if (box.minVert.x > x) {
				box.minVert.x = x;
			}
			if (box.maxVert.x < x) {
				box.maxVert.x = x;
			}

			if (box.minVert.y > y) {
				box.minVert.y = y;
			}
			if (box.maxVert.y < y) {
				box.maxVert.y = y;
			}

			if (box.minVert.z > z) {
				box.minVert.z = z;
			}
			if (box.maxVert.z < z) {
				box.maxVert.z = z;
			}


			tempnum=1;
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(2));
			float x, y, z;
			vn >> x >> y >> z;
		
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(2));
			float x, y, nil;
			vt >> x >> y >> nil;

			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA (VERTEX POSITION/TEXTURE POSITION /TEXTURE NORMAL)
		else if (line.substr(0, 2) == "f ") {	

			if (line.find("/")) {	
				std::replace(line.begin(), line.end(), '/', ' ');
				
				std::stringstream f(line.substr(2));

				int VertexPosition[3];
				int TexturePosition[3];
				int NormalPosition[3];
				
				f >> VertexPosition[0] >> TexturePosition[0] >> NormalPosition[0] >> VertexPosition[1] >> TexturePosition[1] >> NormalPosition[1] >> VertexPosition[2] >> TexturePosition[2] >> NormalPosition[2];
				
				indices.push_back(VertexPosition[0]);
				indices.push_back(VertexPosition[1]);
				indices.push_back(VertexPosition[2]);

				textureIndices.push_back(TexturePosition[0]);
				textureIndices.push_back(TexturePosition[1]);
				textureIndices.push_back(TexturePosition[2]);

				normalIndices.push_back(NormalPosition[0]);
				normalIndices.push_back(NormalPosition[1]);
				normalIndices.push_back(NormalPosition[2]);
			}					
		}
		
		//NEW MESH 
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes(){
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert; 
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.texCoords = textureCoords[textureIndices[i] - 1];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh; 

	subMesh.vertextList = meshVertices; 
	subMesh.meshIndices = indices; 
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear(); 
	normalIndices.clear(); 
	textureIndices.clear(); 
	meshVertices.clear(); 
	currentMaterial = Material();

	std::cout << "Obj File has Loaded!" << std::endl; 
}

void LoadOBJModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}