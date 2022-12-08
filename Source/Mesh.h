#pragma once
#include <vector>
#include "./assimp/scene.h"
#include "GL/glew.h"

class Mesh
{
public:
	~Mesh();

	static Mesh* LoadMesh(const aiMesh* modelMesh);
	void Draw(const std::vector<GLuint>& textureModel);

private:
	Mesh();

	void LoadVBO(const aiMesh* modelMesh);
	void LoadEBO(const aiMesh* modelMesh);
	void CreateVAO();

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	int m_materialIndex;
	int m_numVertices;
	int m_numTriangles;
	int m_numIndices;
};

