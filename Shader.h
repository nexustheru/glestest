#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <sstream>
#include <glm.hpp>
#include <map>
#include <list>


class Shader
{

public:
	   Shader(const char* vertexfile, const char* fragmentfile);
       void ReadFiles(const char* vertexfile, const char* fragmentfile);
       void CreateShader();
	   void compile();
	   void Link();
	   void Use();
	   void Delete();

       void setBool(const std::string& name, bool value) const;

       void setInt(const std::string& name, int value) const;
     
       void setFloat(const std::string& name, float value) const;
      
       void setVec2(const std::string& name, const glm::vec2& value) const;
      
       void setVec2(const std::string& name, float x, float y) const;
      
       void setVec3(const std::string& name, const glm::vec3& value) const;
      
       void setVec3(const std::string& name, float x, float y, float z) const;
     
       void setVec4(const std::string& name, const glm::vec4& value) const;
      
       void setVec4(const std::string& name, float x, float y, float z, float w);
     
       void setMat2(const std::string& name, const glm::mat2& mat) const;
       
       void setMat3(const std::string& name, const glm::mat3& mat) const;
      
       void setMat4(const std::string& name, const glm::mat4& mat) const;

       void getLocations();
       GLuint shader_program;
       std::map <int, std::string > locations;
private:
	int vertex_shader, fragment_shader, stats;
	std::string vert_shader_source, frag_shader_source, info;
};

