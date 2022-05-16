#include "RenderWindow.h"

float angle = 0.0f;

int         pf;
HDC         hDC;
HWND        hWnd;
WNDCLASS    wc;
PIXELFORMATDESCRIPTOR pfd;
static HINSTANCE hInstance = 0;
HGLRC hRC;				/* opengl context */
MSG   msg;				/* message */

RenderWindow::RenderWindow()
{
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 100);
	//glutInitWindowSize(512, 512);
	//glutCreateWindow("Hello, GPGPU! (GLSL version)"); // exits the app

	//glutDisplayFunc(Render);
	//glutReshapeFunc(Resize);
	//glutIdleFunc(Render);

	Initsialize();
}

void RenderWindow::Resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, (float)w / h, 0.01, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}
void RenderWindow::Render(void)
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Enables();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -6.0f, -50.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	if (mods->Faces.size() <= 0)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f, -2.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0);
		glVertex3f(0.0f, 2.0f, 0.0);
		glEnd();
	}
	else
	{
		//glutSolidTeapot(10);
		mods->RenderModel();
	}
	angle += 0.1f;

	glutSwapBuffers();
}
void RenderWindow::Initsialize()
{

	mods = new Model();
	mods->ImportAssimp();
	mods->PrepareModel();
}

void RenderWindow::Enables()
{

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_SPECULAR);
	glEnable(GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DIFFUSE);
	glEnable(GL_SHININESS);
	glEnable(GL_COLOR);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
