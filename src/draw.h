#ifndef DRAW_H
#define DRAW_H
#include <GL/glew.h>
#include "global.h"
namespace glDraw {

double programStartTime = g_timeMs();
float verts[] = { -0.5f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0f,   0.5f,  0.5f, 0.0f };
unsigned int VBO = 0;
const char *vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
unsigned int vertexShader = 0;
const char *fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

void main() {
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";
unsigned int fragmentShader = 0;
unsigned int VAO = 0;


void init() {
	programStartTime = g_timeMs();

	glGenBuffers( 1, &VBO );
	glGenVertexArrays( 1, &VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBindVertexArray( VAO );

	glBufferData( GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW );

	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSrc, NULL );
	glCompileShader( vertexShader );
	int glShaderCompileSuccess;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &glShaderCompileSuccess );
	if (!glShaderCompileSuccess) {
		char infoLog[512];
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		fprintf( stderr, "Vertex Shader Compilation Failure: %s\n", infoLog );
	}

	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderSrc, NULL );
	glCompileShader( fragmentShader );

	{
		int glShaderCompileSuccess;
		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &glShaderCompileSuccess );
		if (!glShaderCompileSuccess) {
			char infoLog[512];
			glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
			fprintf( stderr, "Fragment Shader Compilation Failure: %s\n", infoLog );
		}
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	{
		int shaderProgramLinkSuccess;
		glGetProgramiv( shaderProgram, GL_LINK_STATUS, &shaderProgramLinkSuccess );
		if (!shaderProgramLinkSuccess) {
			char infoLog[512];
			glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
			fprintf( stderr, "Shader Program Linker Failure: %s\n", infoLog );
		}
	}

	glUseProgram(shaderProgram);

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );
}

void cleanup() {
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
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


	glDrawArrays( GL_TRIANGLES, 0, 3 );
}


} // namespace glDraw
#endif // #define DRAW_H