#include "TestClearColor.h"

#include "Renderer.h"


namespace TestSpace {

	TestClearColor::TestClearColor() :
		m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.f }
	{
	}


	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float DeltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("ClearColor", m_ClearColor);
	}

}
