// SDLProj.cpp : Defines the entry point for the console application.

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "Renderer.h"
#include "Tests/TestClearColor.h"
#include "Tests/Test3DBox.h"
#include "Tests/Test3DBox36.h"
#include "Tests/Test3DBoxMany.h"

inline static bool WindowShouldClose(const SDL_Event& e)
{
	return (
		e.type == SDL_QUIT
	|| (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
	|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
	);
}

inline static float GetDeltaTime()
{
	static Uint32 LastTick = 0;
	const Uint32 Ticks = SDL_GetTicks();
	const Uint32 Tmp = LastTick;
	LastTick = Ticks;
	return (Ticks - Tmp) / 1000.f;
}

int main()
{
	using namespace TestSpace;

	Renderer R(600, 1000, SDL_WINDOW_RESIZABLE);

	std::unique_ptr<Test> AllTests[] = {
		std::make_unique<TestClearColor>(),
		//std::make_unique<Test3DBox>(R),
		//std::make_unique<Test3DBox36>(R),
		std::make_unique<Test3DBoxMany>(R)
	};

	Test *CurrentTest = nullptr;
	int TestPicker = -1;
	bool ShowAnotherWindow = true;

	// main loop
	bool ShouldClose = false;

	SDL_Event	e;
	while (!ShouldClose)
	{
		// MUST BE HERE
		R.Clear();
		//

		ImGui_ImplSdlGL3_ProcessEvent(&e);
		while (SDL_PollEvent(&e))
			ShouldClose = WindowShouldClose(e);

		ImGui::Begin("Test", &ShowAnotherWindow);
		ImGui::Text("Choose one of the tests");
		if (
				ImGui::RadioButton("Test ClearColor", &TestPicker, 0)
			||	ImGui::RadioButton("Test 3D Cube with 8 vertices", &TestPicker, 1)
			||	ImGui::RadioButton("Test 3D Cube with 36 vertices", &TestPicker, 2)
			||	ImGui::RadioButton("Test with a lot of 3D cubes", &TestPicker, 3)
		)
		{
			CurrentTest = AllTests[TestPicker].get();
		}
		ImGui::End();

		if (CurrentTest)
		{
			CurrentTest->OnUpdate(GetDeltaTime());
			CurrentTest->OnRender();
			CurrentTest->OnImGuiRender();
		}
		R.UpdateWindow();
	}
	return 0;
}
