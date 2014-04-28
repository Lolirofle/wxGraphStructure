#include "gl.hpp"

void glInit2D(int x,int y,int w,int h,uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha){
	glClearColor(red/255.0f,green/255.0f,blue/255.0f,alpha/255.0f);
	glEnable(GL_TEXTURE_2D);
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

void glLineRect(float x1,float y1,float x2,float y2){
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y1);
	glEnd();
}
