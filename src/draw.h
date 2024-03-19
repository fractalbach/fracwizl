#ifndef DRAW_H
#define DRAW_H
#include <string>
#include <GL/glew.h>
#include "global.h"
#include "loader.h"
namespace glDraw {


const float z = 0.0f;
const float a = 0.5f;
const float o = 1.0f;

float justVerts[] = { -a,-a,z, a,-a,z, -a,a,z, a,a,z };
float justColors[] = { o,z,z, z,o,z, z,z,o, o,z,z };
unsigned int indices[] = { 0,1,2, 2,1,3 };

const int nVerts = 4;
const int nAttributes = 2;
const int vertDataLen = nVerts * nAttributes * 3;
float vertData[ vertDataLen ];

double programStartTime = g_timeMs();
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

	// package up the vert data to feed to the VAO
	for (int i=0; i<nVerts; i++) {
		for (int j=0; j<3; j++) {
			vertData[ 6*i + j ] = justVerts[ 3*i + j ];
			vertData[ 6*i + 3 + j ] = justColors[ 3*i + j ];
		}
	}

	glGenBuffers( 1, &VBO );
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &EBO );
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	shaderProgram = glCreateProgram();
}


void reload() {

	// Load data from files

	std::string vertexShaderSrc = loader::loadFile( "src/shaders/basic.vert" );
	std::string fragmentShaderSrc = loader::loadFile( "src/shaders/basic.frag" );
	const char* cVertexShaderSrc = vertexShaderSrc.c_str();
	const char* cFragmentShaderSrc = fragmentShaderSrc.c_str();

	// Update Vertex Data

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBindVertexArray( VAO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );

	glBufferData( GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

	// vertex attributes
	const int stride = 6*sizeof(float);
	const int colorOffset = 3*sizeof(float);
	// attribute: position
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0 );
	glEnableVertexAttribArray( 0 );
	// attribute: color
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, stride, (void*)colorOffset );
	glEnableVertexAttribArray( 1 );

	// Compile Shaders

	glShaderSource( vertexShader, 1, &cVertexShaderSrc, NULL );
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

	glShaderSource( fragmentShader, 1, &cFragmentShaderSrc, NULL );
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

	// Link Shaders

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

	glUniform1f( glGetUniformLocation( shaderProgram, "iTime" ), iTime );
	glUniform2ui( glGetUniformLocation( shaderProgram, "iResolution" ), width, height );

	glUseProgram( shaderProgram );
	glBindVertexArray( VAO );
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
}


} // namespace glDraw
#endif // #ifndef DRAW_H