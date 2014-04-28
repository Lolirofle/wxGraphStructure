#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GL_H_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GL_H_INCLUDED__

// include OpenGL
#ifdef __WXMAC__
#   include "OpenGL/gl.h"
#else
#   include <GL/gl.h>
#endif

/**
 * Initiate 2d rendering
 */
void glInit2D(int x,int y,int w,int h);

#endif
