#pragma once

#include <string>
#include <list>

#include "./assimp/scene.h"

#include "Mesh.h"

class Model
{
public:
	~Model();

	static const std::string FolderPath;

	static Model* LoadFile(const std::string& fileName);
	void Draw();

private:
	Model(std::string i_fileName);

	static bool CheckValidFormat(const std::string& fileName);
	void LoadMaterials(const aiScene* scene);
	void LoadMeshes(aiMesh** meshes, int numMeshes);

	std::vector<GLuint> textures;
	std::list<Mesh*> myMeshes;
	std::string modelFolder;
};

