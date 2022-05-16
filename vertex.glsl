#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 colorr;

uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 models;
uniform mat4 mvp; 

out vec3 Normal;
out vec4 cols;
out vec2 tex;

void main()
{
    
    Normal = normals;    	
    gl_Position = mvp * vec4(position, 20);//savethis shit
	cols=colorr;
	tex=texCoord;
}