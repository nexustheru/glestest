#include "Model.h"


#define glCheckError() glCheckError_(__FILE__, __LINE__)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void Model::PrepareImage()
{
	if (textures.empty() == false)
	{
		GLuint texture[sizeof(textures)];
		glGenTextures(textures.size(), texture);
		for( int p = 0; p < textures.size();p++)
		{
			int width, height, bpp;
			stbi_set_flip_vertically_on_load(true);
			uint8_t* rgb_image = stbi_load(textures[p].c_str(), &width, &height, &bpp, STBI_rgb_alpha);
			
			if (rgb_image == nullptr)
			{
						std::cout << " cant open " << textures[p].c_str() <<  std::endl;
						stbi_image_free(rgb_image);
			}
			else
			{
				std::cout << "Image been loaded" << std::endl;
	
				glBindTexture(GL_TEXTURE_2D, texture[p]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgb_image);
				
	            stbi_image_free(rgb_image);
			}
		
		}
	}
}
void Model::PrepareModel()
{
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //pos
    glEnableVertexAttribArray(VPosition);
	glVertexAttribPointer(VPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//some error here

	//glBindBuffer(GL_ARRAY_BUFFER, NORM);
	//glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(float) * 3, &nor[0], GL_STATIC_DRAW); //pos
	glEnableVertexAttribArray(NPosition);
	glVertexAttribPointer(NPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//glCheckError();
	//glBindBuffer(GL_ARRAY_BUFFER, TEXBUFF);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //pos
	glEnableVertexAttribArray(UPosition);
	glVertexAttribPointer(UPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	//glBindBuffer(GL_ARRAY_BUFFER, COLORBUFF);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //pos
	glEnableVertexAttribArray(CPosition);
	glVertexAttribPointer(CPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colors));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Faces.size() * sizeof(Triangle), &Faces[0], GL_STATIC_DRAW);//fac


	glBindVertexArray(0);
	//glUseProgram(0);	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	std::cout << "model is prepared" << std::endl;

}
void Model::RenderModel()
{
	
    UseShader();
    Matrixes();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (unsigned int)Faces.size() * (unsigned int)3, GL_UNSIGNED_INT, (void*)0);
	
	glBindVertexArray(0);
	glUseProgram(0);
}
void Model::ImportAssimp(void)
{
	Assimp::Importer importer;

	sce = importer.ReadFile("ball.fbx", aiProcess_Triangulate | aiProcessPreset_TargetRealtime_MaxQuality);


	if (!sce)
	{
		std::cout << importer.GetErrorString() << std::endl;
	}

	else
	{
			root = sce->mRootNode;

		for (unsigned int i = 0; i < sce->mNumMeshes; i++)
		{
			const aiMesh* amesh = sce->mMeshes[i];
			for (unsigned int v = 0; v < amesh->mNumVertices; v++)
			{
				Vertex vert;
				vert.Position= convertAivector3(amesh->mVertices[v]);
				vert.Normal = convertAivector3(amesh->mNormals[v]) ;
				
				if (amesh->mTextureCoords[0])
				{
					vert.TexCoords =  convertAivector2(amesh->mTextureCoords[0][v]) ;
					
				}
				if (amesh->HasVertexColors(0))
				{
					vert.Colors = convertAivector4(amesh->mColors[0][v]);

				}

				this->vertices.push_back(vert);
				
			}

			for (unsigned int f = 0; f < amesh->mNumFaces; f++)
			{
				aiFace assimpFace = amesh->mFaces[f];
				Triangle facee;
				for (unsigned int j = 0; j < assimpFace.mNumIndices; j++)
				{
					facee.face[j] = assimpFace.mIndices[j];
				}
				Faces.push_back(facee);
			}

	
		}
	
		if (sce->HasMaterials())
		{
			for (unsigned te = 0; te < sce->mNumMaterials; te++)
			{
				aiMaterial* mats = sce->mMaterials[te];
				materials.push_back(mats);
				std::cout << "Material added" << std::endl;
			}
		}

			if (sce->HasTextures())
			{

				for (unsigned int m = 0; m < sce->mNumMaterials; m++)
				{
					int texIndex = 0;
					aiReturn texFound = AI_SUCCESS;

					aiString path;	// filename

					while (texFound == AI_SUCCESS)
					{
						texFound = sce->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
						
						textures.push_back(path.C_Str());
						std::cout << "texture added" << std::endl;
						texIndex++;
					}
				}
				PrepareImage();
			}
	
		std::cout << "Vertex: " << sizeof(offsetof(Vertex, Position)) << std::endl;
		std::cout << "Normals: " << sizeof(offsetof(Vertex, Normal)) << std::endl;
		std::cout << "Coords: " << sizeof(offsetof(Vertex, TexCoords)) << std::endl;
		std::cout << "Colors: " << sizeof(offsetof(Vertex, Colors)) << std::endl;
		std::cout << "Faces: " << Faces.size() << std::endl;
		std::cout << "Assimp uploaded" << std::endl;

	}


}

void Model::CreateShader()
{
	ifstream v("vertex.glsl");
	if (v.is_open())
	{
		std::cout << "Vertex file is open" << std::endl;
		string str;
		ostringstream ss;
		ss << v.rdbuf(); // reading data
		vert_shader_source = ss.str();
	}
	v.close();

	ifstream fv("fragment.glsl");
	if (fv.is_open())
	{
		std::cout << "Fragment file is open" << std::endl;
		string str;
		ostringstream ss;
		ss << fv.rdbuf(); // reading data
		frag_shader_source = ss.str();
	}
	fv.close();
	
	const char* ve = vert_shader_source.c_str();
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &ve, NULL);
	std::cout << "vertex source created" << std::endl;

	const char* fa = frag_shader_source.c_str();
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fa, NULL);
	std::cout << "Fragment source created" << std::endl;

	//vertex
	GLsizei log1Length;
	GLchar  log1[1024];
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &stats);
	if (!stats)
	{
		glGetShaderInfoLog(vertex_shader, sizeof(log1), &log1Length, log1);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log1 << std::endl;
	}
	//fragment
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &stats);
	if (!stats)
	{
		glGetShaderInfoLog(fragment_shader, sizeof(log1), &log1Length, log1);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log1 << std::endl;
	}
	std::cout << "Fragment and Vertex compiled" << std::endl;
	ShaderId = glCreateProgram();
	glAttachShader(ShaderId, vertex_shader);
	glAttachShader(ShaderId, fragment_shader);

	glLinkProgram(ShaderId);
	glGetProgramiv(ShaderId, GL_LINK_STATUS, &stats);
	if (!stats)
	{
		glGetProgramInfoLog(ShaderId, 512, NULL, log1);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log1 << std::endl;
	}
	else
	{
		std::cout << "Shader Program is linked" << std::endl;
	VPosition = glGetAttribLocation(ShaderId, "position");
	NPosition = glGetAttribLocation(ShaderId, "normals");
	UPosition = glGetAttribLocation(ShaderId, "texCoord");
	CPosition = glGetAttribLocation(ShaderId, "colorr");

	ModelView = glGetUniformLocation(ShaderId, "models");
	Projection = glGetUniformLocation(ShaderId, "projection");
	View = glGetUniformLocation(ShaderId, "view");
	MVP = glGetUniformLocation(ShaderId, "mvp");

	//PicPosition = MVP = glGetUniformLocation(ShaderId, "pic");
	}

	
}
void Model::UseShader()
{

	glUseProgram(ShaderId);

}

GLenum Model::glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}

void Model::Matrixes()
{
	glm::mat4x4* assi = new glm::mat4x4(FromMatrix(root->mTransformation));
	
	float aspect =height / width;

	float zoom = 80.0f;
	//PROJECTION
	glm::mat4 Projectionn = glm::perspective(45.0f, aspect, 0.1f, 100.0f);

	//VIEW
	glm::mat4 Vieww = glm::mat4(1.);
	Vieww = glm::translate(Vieww, glm::vec3(0.0F, 0.0F, -3.0F));

	//MODEL
	glm::mat4 Modell = glm::mat4(1.0);
	//Scale by factor 0.5
	Modell = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	glm::mat4 MVPp = Projectionn * Vieww * Modell;
	
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, glm::value_ptr(Modell));
	glUniformMatrix4fv(Projection, 1, GL_TRUE, glm::value_ptr(Projectionn));
	glUniformMatrix4fv(View, 1, GL_TRUE, glm::value_ptr(Vieww));
	glUniformMatrix4fv(MVP, 1, GL_TRUE, glm::value_ptr(MVPp));
}
glm::vec3 Model::convertAivector3(aiVector3D in)
{
	glm::vec3 out = { glm::vec3(in.x, in.y, in.z) };
	return out;
}
glm::vec2 Model::convertAivector2(aiVector3D in)
{
	glm::vec2 out = {glm::vec2(in.x, in.y)};
	return out;
}
glm::vec4 Model::convertAivector4(aiColor4D in)
{
	glm::vec4 out = { glm::vec4(in.r, in.g, in.b, in.a)};
	return out;
}
glm::mat4x4 Model::FromMatrix(aiMatrix4x4 mat)
{
	glm::mat4x4 m{mat.a1,mat.a2,mat.a3,mat.a4,mat.b1,mat.b2,mat.b3,mat.b4,mat.c1,mat.c2,mat.c3,mat.c4,mat.d1,mat.d2,mat.d3,mat.d4 };
	return m;
}