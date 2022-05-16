#version 330 core

in vec3 Normal;
in vec4 cols;
in vec2 tex;

out vec4 FragColor;
uniform sampler2D pic;

void main()
{     
    FragColor = texture2D(pic, tex);
	//FragColor = vec4(cols,1);
    
}