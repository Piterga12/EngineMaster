#include "Model.h"

#include <vector>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTexture.h"

#include "./assimp/cimport.h"
#include "./assimp/postprocess.h"

const std::string Model::FolderPath = "models/";

Model::Model(std::string fileName)
{
	while (0 < fileName.size() && fileName[fileName.size() - 1] != '\\') {
		fileName.pop_back();
	}	
	modelFolder = fileName;
}

Model::~Model()
{
	glDeleteTextures(textures.size(), &textures[0]);
	for (Mesh* mesh : myMeshes) {
		delete mesh;
	}	
	myMeshes.clear();
}

Model* Model::LoadFile(const std::string& fileName)
{
	Model* model = new Model(fileName);

	std::string filePath = fileName;
	const aiScene* scene = aiImportFile(filePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	

	if (scene)
	{
		//PERSLOG("%s", fileName);
		model->LoadMaterials(scene);
		if (model->textures.size() != scene->mNumMaterials) {
			aiReleaseImport(scene);
			return nullptr;
		}
		model->LoadMeshes(scene->mMeshes, scene->mNumMeshes);
		aiReleaseImport(scene);
		return model;
	}
	else
	{
		return nullptr;
	}
}

bool Model::CheckValidFormat(const std::string& i_fileName)
{
	std::string fileFormat;
	bool dotNotFound = true;
	for (int i = i_fileName.size() - 1; dotNotFound && 0 <= i; --i) {
		char currentChar = i_fileName[i];
		fileFormat.insert(fileFormat.begin(), currentChar);
		dotNotFound = currentChar != '.';
	}
	return fileFormat == ".fbx";
}

void Model::Draw()
{
	for (std::list<Mesh*>::iterator it = myMeshes.begin(); it != myMeshes.end(); ++it) {
		(*it)->Draw(textures);
	}
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	//PERSLOG("%i", scene->mNumMaterials)

	textures.reserve(scene->mNumMaterials);

	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			GLuint texture = App->texture->LoadTextureFromFile(file.data, modelFolder);
			if (texture == -1) { //Error, failed to load the texture
				return;
			}
			textures.push_back(texture);
		}
	}
}

void Model::LoadMeshes(aiMesh** meshes, int numMeshes)
{
	for (int i = 0; i < numMeshes; ++i) {
		Mesh* mesh = Mesh::LoadMesh(meshes[i]);
		myMeshes.push_back(mesh);
	}
}
