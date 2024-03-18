#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "global.h"
#include "intro.h"
#include "draw.h"

int main() {
	printf( "%s", (const char *)INTRO_TEXT );

	const char * title = "FWIZL";
	int width = g_defaultScreenWidth;
	int height = g_defaultScreenHeight;

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_Window * window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if ( !window ) {
		fprintf( stderr, "Window creation failed: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext( window );
	if ( !glContext ) {
		fprintf( stderr, "OpenGL Context creation error: %s\n", SDL_GetError() );
		return 1;
	}

	GLenum glewResult = glewInit();
	if ( glewResult != GLEW_OK ) {
		fprintf( stderr, "GLEW Init failed: %s\n", glewGetErrorString(glewResult) );
		return 1;
	}

	bool quit = false;

	glDraw::init();

	while ( !quit ) {
		SDL_Event event;
		while ( SDL_PollEvent(&event) ) {
			if ( event.type == SDL_QUIT ) {
				quit = true;
			}
		}

		glDraw::frame();

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	SDL_Quit();
}
