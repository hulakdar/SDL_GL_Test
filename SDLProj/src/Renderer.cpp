#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>

Renderer::Renderer(int WinHeight, int WinWidth, Uint32 AdditionalSdlWindowFlags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL ERROR: " << SDL_GetError() << "\n";
		exit(-1);
	}

	unsigned int ImgInitFlags = IMG_INIT_PNG;
	if (!(IMG_Init(ImgInitFlags) & ImgInitFlags))
	{
		std::cerr << "SDL_image ERROR: " << IMG_GetError() << "\n";
		exit(-1);
	}
	
	SDL_GL_SetSwapInterval(1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// SDL_WINDOW_OPENGL flag is a must
	Window = SDL_CreateWindow(
		"SDL Test", // Window name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // position
		WinWidth, WinHeight, // width, height
		SDL_WINDOW_OPENGL | AdditionalSdlWindowFlags // flags
	);

	// creating an opengl context
	SdlGlContext = SDL_GL_CreateContext(Window);

	if (GLenum Result = glewInit() != GLEW_OK)
	{
		const char *error = (const char *)glewGetErrorString(Result);
		std::cerr << "GLEW ERROR!\n";
		std::cerr << error << "\n";
		exit(-1);
	}

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	io = &ImGui::GetIO();

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSdlGL3_Init(Window);

	// Setup style
	ImGui::StyleColorsDark();

    io->Fonts->AddFontFromFileTTF("res/fonts/Roboto-Medium.ttf", 16.0f);

	GLCall(glEnable(GL_DEPTH_TEST));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}


Renderer::~Renderer()
{
    ImGui_ImplSdlGL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(SdlGlContext);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	ImGui_ImplSdlGL3_NewFrame(Window);
}

void Renderer::Draw(const VertexArray & Va, const Shader & Program, const IndexBuffer & Ib) const
{
	Program.Bind();
	Va.Bind();
	Ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, Ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::Draw(const VertexArray & Va, const Shader & Program, unsigned int Count) const
{
	Program.Bind();
	Va.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, Count));
}

void Renderer::UpdateWindow() const
{
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(Window);
}

SDL_Window * Renderer::GetWindow() const
{
	return Window;
}
