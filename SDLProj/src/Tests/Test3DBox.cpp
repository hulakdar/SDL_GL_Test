#include "Test3DBox.h"


namespace TestSpace {

	Test3DBox::Test3DBox(const Renderer& Renderer) :
		m_Renderer(Renderer),
		m_VertexBuffer(std::vector<float>
		{
				-0.5f, -0.5f, -0.5f, 1.f, 1.f,  // 0
				 0.5f, -0.5f, -0.5f, 1.f, 0.f,  // 1
				 0.5f,  0.5f, -0.5f, 0.f, 0.f,  // 2
				-0.5f,  0.5f, -0.5f, 0.f, 1.f,  // 3
				 0.5f,  0.5f,  0.5f, 0.f, 1.f,  // 4
				-0.5f,  0.5f,  0.5f, 0.f, 0.f,  // 5
				-0.5f, -0.5f,  0.5f, 1.f, 0.f,  // 6
				 0.5f, -0.5f,  0.5f, 1.f, 1.f,  // 7
		}),
		m_IndexBuffer(std::vector<unsigned int>
		{
				0, 3, 5, // left face
				6, 0, 5,
				4, 2, 1, // right face
				4, 1, 7,
				6, 5, 4, // front face
				7, 6, 4,
				1, 2, 3, // back face
				1, 3, 0,
				3, 2, 4, // top face
				3, 4, 5,
				1, 0, 7, // bottom face
				0, 6, 7
		}),
		m_Program("res/shaders/Vertex.shader", "res/shaders/ColorFragment.shader"),
		m_Texture("res/sample2.png")
	{
		m_VertexBufferLayout.Push<float>(3);
		m_VertexBufferLayout.Push<float>(2);
		m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);
	}

	Test3DBox::~Test3DBox() {}

	void Test3DBox::OnUpdate(float DeltaTime)
	{
		m_RotationAngle += DeltaTime;
		m_Model = glm::translate(glm::rotate(glm::rotate(glm::mat4(1.f), sin(m_RotationAngle), glm::vec3(0.f, 1.f, 0.f)), m_RotationAngle, glm::vec3(0.f, 0.f, 1.f)), m_Translation);
		m_Program.SetUniform("u_MVP", m_Model);
	}

	void Test3DBox::OnRender()
	{
		m_Texture.Bind();
		m_Renderer.Draw(m_VertexArray, m_Program, m_IndexBuffer);
	}

	void Test3DBox::OnImGuiRender()
	{
		ImGui::SliderFloat3("Box Translation", &m_Translation[0], -1.f, 1.f);
	}
}
