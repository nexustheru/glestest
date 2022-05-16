#pragma once
#include <vector>
//#include <GL/glew.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <assimp\Importer.hpp>
#include <assimp\Exporter.hpp>
#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp/matrix4x4.h>
#include <assimp\config.h>
#include <assimp\material.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec4 Colors;
};

struct Triangle
{
	unsigned int face[3];
};

struct Image
{
	std::string path;
	
};

class Model
{
public:
	std::vector <Vertex> vertices;
	std::vector <glm::vec3> nor;
	std::vector <Triangle> Faces;
	
	std::vector<aiMaterial*> materials;
	std::vector<std::string> textures;

	void ImportAssimp(void);
	void RenderModel(void);
	void PrepareImage();
	void PrepareModel(void);
	void CreateShader();
	void UseShader();
	
	GLenum glCheckError_(const char* file, int line);

	glm::vec3 convertAivector3(aiVector3D in);
	glm::vec2 convertAivector2(aiVector3D in);
	glm::vec4 convertAivector4(aiColor4D in);
	glm::mat4x4 FromMatrix(aiMatrix4x4 mat);
	void Matrixes();

	unsigned int VAO, VBO, EBO, NORM,TEXBUFF,COLORBUFF,TEXTUREID;

	float height, width;
	int ModelView, Projection, View,MVP, VPosition, NPosition, UPosition, CPosition,ShaderId,PicPosition;
	int vertex_shader, fragment_shader, stats;
	std::string vert_shader_source, frag_shader_source, info;
private:
	
	aiNode* root;
	const aiScene* sce;

};

