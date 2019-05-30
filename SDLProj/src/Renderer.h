#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#undef main

#include "Wrapper.h"

class Renderer
{
private:
	SDL_Window *Window;
	SDL_GLContext SdlGlContext;
	ImGuiIO* io;
public:
	Renderer(int WinHeight = 300, int WinWidth = 500, Uint32 AdditionalSdlWindowFlags = 0);
	~Renderer();

	void Clear() const ;
	void Draw(const class VertexArray& Va, const class Shader& Program, const class IndexBuffer& Ib) const ;
	void Draw(const VertexArray & Va, const Shader & Program, unsigned int Count) const;
	void UpdateWindow() const;
	SDL_Window *GetWindow() const;
};

