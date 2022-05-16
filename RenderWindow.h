#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Model.h"

class RenderWindow
{
public:
	RenderWindow();
	void Resize(int w, int h);
	void Render(void);
	void Initsialize();
	void Enables();

private:
	  //
	  
	  //
	  int width = 512;
	  int height = 512;
	  Model* mods;

};

