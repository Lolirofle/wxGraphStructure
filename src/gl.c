#include "gl.h"

void glInit2D(int x,int y,int w,int h){
	glClearColor(0.0f,0.0f,0.0f,1.0f); // Black Background
	glEnable(GL_TEXTURE_2D);   // textures
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glViewport(x,y,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(x,w,h,y,1,-1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
