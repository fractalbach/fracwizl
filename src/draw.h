#ifndef DRAW_H
#define DRAW_H
#include <GL/glew.h>
#include "global.h"
#include "shaders/hex/basic_vert.h"
namespace glDraw {

double programStartTime = g_timeMs();
float verts[] = { -0.5f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0f,   0.5f,  0.5f, 0.0f };
unsigned int VBO = 0;
const char *vertexShaderSrc = (const char *)src_shaders_basic_vert;
unsigned int vertexShader = 0;

void init() {
	programStartTime = g_timeMs();

	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW );

	// vertexShader = glCreateShader( GL_VERTEX_SHADER );
	// glShaderSource( vertexShader, 1, &vertexShaderSrc, NULL );
	// glCompileShader( vertexShader );
	// int glShaderCompileSuccess;
	// glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &glShaderCompileSuccess );
	// if (!glShaderCompileSuccess) {
	// 	char infoLog[512];
	// 	glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
	// 	fprintf( stderr, "Shader Compilation Failure: %s\n", infoLog );
	// }
}

void frame() {
	double timeCurrent = g_timeMs() - programStartTime;
	float iTime = float(timeCurrent);

	// some neato effects
	float r = 0.5 + 0.5 * cosf( iTime );
	float g = 0.5 + 0.5 * cosf( iTime + 2.0f );
	float b = 0.5 + 0.5 * cosf( iTime + 4.0f );
	glClearColor( r, g, b, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace glDraw
#endif // #define DRAW_H