#pragma once

#define GLCall(x) \
	GLClearError();\
	x;\
	SDL_assert(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();

bool GLCheckError(const char *Function, const char *File, int Line);