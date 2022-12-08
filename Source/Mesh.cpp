#include "Mesh.h"

#include ".\libs\MathGeoLib\Include\Math\float2.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleCamera.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VAO);
}

Mesh* Mesh::LoadMesh(const aiMesh* modelMesh)
{
	Mesh* mesh = new Mesh();
	mesh->m_materialIndex = modelMesh->mMaterialIndex;
	mesh->m_numTriangles = modelMesh->mNumFaces;
	mesh->LoadVBO(modelMesh);
	mesh->LoadEBO(modelMesh);
	mesh->CreateVAO();
	return mesh;
}

void Mesh::Draw(const std::vector<GLuint>& textureModel)
{
	GLuint program = App->rendererExercise->GetProgram();
	const float4x4& view = App->camera->GetView();
	const float4x4& proj = App->camera->GetProjection();
	float4x4 model = float4x4::identity;
	
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);
	
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, textureModel[m_materialIndex]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::LoadVBO(const aiMesh* modelMesh)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	GLuint vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	GLuint buffer_size = vertex_size * modelMesh->mNumVertices;
	
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	
	GLuint position_size = sizeof(float) * 3 * modelMesh->mNumVertices;
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, modelMesh->mVertices);
	
	GLuint uv_offset = position_size;
	GLuint uv_size = sizeof(float) * 2 * modelMesh->mNumVertices;
	
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	
	for (int i = 0; i < modelMesh->mNumVertices; ++i)
	{
		uvs[i] = float2(modelMesh->mTextureCoords[0][i].x, modelMesh->mTextureCoords[0][i].y);
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	m_numVertices = modelMesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* modelMesh)
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	GLuint index_size = sizeof(GLuint) * modelMesh->mNumFaces * 3;
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	
	GLuint* indices = (GLuint*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	
	for (int i = 0; i < modelMesh->mNumFaces; ++i)
	{
		assert(modelMesh->mFaces[i].mNumIndices == 3);
		*(indices++) = modelMesh->mFaces[i].mIndices[0];
		*(indices++) = modelMesh->mFaces[i].mIndices[1];
		*(indices++) = modelMesh->mFaces[i].mIndices[2];
	}
	
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
	m_numIndices = modelMesh->mNumFaces * 3;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * m_numVertices));
}
