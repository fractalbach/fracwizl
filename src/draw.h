#ifndef DRAW_H
#define DRAW_H
#include <GL/glew.h>
#include "global.h"
namespace glDraw {

const char *vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char *fragmentShaderSrc = R"(
#version 330 core
out vec4 fragColor;

uniform float iTime;
uniform uvec2 iResolution;

void main() {
	vec3 col = 0.5 + 0.5 * cos( iTime + vec3(2,4,6) );
	fragColor = vec4( col, 1.0 );
}
)";

const int SLOT_UNIFORM_TIME = 0;
const int SLOT_UNIFORM_RES = 1;

double programStartTime = g_timeMs();
const float z = 0.0f;
// const float a = 1.0f;
const float a = 0.5f;
// float verts[] = { a,a,z, a,-a,z, -a,-a,z, -a,a,z };
// unsigned int indices[] = { 0,1,3, 1,2,3 };
float verts[] = { -a,-a,z, a,-a,z, -a,a,z, a,a,z };
unsigned int indices[] = { 0,1,2, 2,1,3 };
unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int EBO = 0;
unsigned int vertexShader = 0;
unsigned int fragmentShader = 0;
unsigned int shaderProgram = 0;
bool setting_wireframeMode = false;
int width = g_defaultScreenWidth;
int height = g_defaultScreenHeight;



void init() {
	programStartTime = g_timeMs();

	glGenBuffers( 1, &VBO );
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &EBO );
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	shaderProgram = glCreateProgram();
}

void reload() {
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBindVertexArray( VAO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );

	glBufferData( GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glShaderSource( vertexShader, 1, &vertexShaderSrc, NULL );
	glCompileShader( vertexShader );

	{
		int glShaderCompileSuccess;
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &glShaderCompileSuccess );
		if (!glShaderCompileSuccess) {
			char infoLog[512];
			glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
			fprintf( stderr, "Vertex Shader Compilation Failure: %s\n", infoLog );
		}
	}

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
}

void onWindowResize( int w, int h ) {
	width = w;
	height = h;
	glViewport( 0, 0, w, h );
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

	if (setting_wireframeMode) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	} else {
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	glUniform1f( 0, iTime );
	glUniform2ui( 1, width, height );


	glUseProgram( shaderProgram );
	glBindVertexArray( VAO );
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
}


} // namespace glDraw
#endif // #define DRAW_H