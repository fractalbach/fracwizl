#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "global.h"
#include "intro.h"
#include "draw.h"

int main() {

	const char * title = "FWIZL";
	bool quit = false;

	printf( "%s", (const char *)INTRO_TEXT );

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	SDL_Window * window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_defaultScreenWidth, g_defaultScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	if ( !window ) {
		fprintf( stderr, "Window creation failed: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext( window );
	if ( !glContext ) {
		fprintf( stderr, "OpenGL Context creation error: %s\n", SDL_GetError() );
		return 1;
	}

	glewExperimental = GL_TRUE;
	GLenum glewResult = glewInit();
	if ( glewResult != GLEW_OK ) {
		fprintf( stderr, "GLEW Init failed: %s\n", glewGetErrorString(glewResult) );
		return 1;
	}

	printf( "GL_VENDOR=(%s)\n", glGetString(GL_VENDOR) );
	printf( "GL_RENDERER=(%s)\n", glGetString(GL_RENDERER) );
	printf( "GL_VERSION=(%s)\n", glGetString(GL_VERSION) );
	printf( "GL_SHADING_LANGUAGE_VERSION=(%s)\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );

	glDraw::init();
	glDraw::reload();

	while ( !quit ) {
		SDL_Event event;
		while ( SDL_PollEvent(&event) ) {
			switch ( event.type ) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					glDraw::onWindowResize( event.window.data1, event.window.data2 );
				}
				break;
			}
		}
		glDraw::frame();
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	SDL_Quit();
}

