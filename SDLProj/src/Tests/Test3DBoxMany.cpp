#include "Test3DBoxMany.h"

namespace TestSpace {

	Test3DBoxMany::Test3DBoxMany(const Renderer& Renderer) :
		m_Renderer(Renderer),
		m_VertexBuffer(std::vector<float>
		{
		    -0.5f, -0.5f, -0.5f, 0.0f,0.0f, 0.0f,0.0f, -1.0f,
		  	 0.5f, -0.5f, -0.5f, 1.0f,0.0f, 0.0f,0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,1.0f, 0.0f,0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,1.0f, 0.0f,0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f,1.0f, 0.0f,0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f,0.0f, 0.0f,0.0f, -1.0f,
                        
			-0.5f, -0.5f,  0.5f, 0.0f,0.0f, 0.0f,0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f,1.0f, 0.0f,0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f,0.0f, 0.0f,0.0f, 1.0f,
                        
			-0.5f,  0.5f,  0.5f, 1.0f,0.0f, -1.0f,0.0f,0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f,1.0f, -1.0f,0.0f,0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f,1.0f, -1.0f,0.0f,0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f,1.0f, -1.0f,0.0f,0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f,0.0f, -1.0f,0.0f,0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f,0.0f, -1.0f,0.0f,0.0f,
                        
			 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 1.0f,0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,1.0f, 1.0f,0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 0.0f,0.0f, 1.0f,0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 1.0f,0.0f, 0.0f,
                         
			-0.5f, -0.5f, -0.5f, 0.0f,1.0f, 0.0f,-1.0f,0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f,1.0f, 0.0f,-1.0f,0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f,0.0f, 0.0f,-1.0f,0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f,0.0f, 0.0f,-1.0f,0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f,0.0f, 0.0f,-1.0f,0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f,1.0f, 0.0f,-1.0f,0.0f,
                         
			-0.5f,  0.5f, -0.5f, 0.0f,1.0f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,1.0f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 0.0f,1.0f,0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f,0.0f, 0.0f,1.0f,0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f,1.0f, 0.0f,1.0f,0.0f
		}),
		m_Program("res/shaders/PhongVertex.shader", "res/shaders/PhongFragment.shader"),
		m_LightSourceShader("res/shaders/SimpleVertex.shader", "res/shaders/LightSourceFragment.shader"),
		m_Texture("res/sample2.png")
	{
		m_VertexBufferLayout.Push<float>(3);
		m_VertexBufferLayout.Push<float>(2);
		m_VertexBufferLayout.Push<float>(3);
		m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

	}

	Test3DBoxMany::~Test3DBoxMany() {}

	void Test3DBoxMany::OnUpdate(float DeltaTime)
	{
		m_RotationAngle += DeltaTime;
	}

	void Test3DBoxMany::OnRender()
	{
		const glm::vec3 CubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		int x, y;
		SDL_GetWindowSize(m_Renderer.GetWindow(), &x, &y);
		m_ViewProjectionMatrix = glm::perspective(glm::radians(65.0f), x/(float)y, 0.1f, 100.0f) * glm::translate(glm::mat4(1), glm::vec3(0.0f, 5 * sin(m_RotationAngle), -3.0f));

		const glm::vec3 LightPosition(0.f, 0.f, -10.f);
		m_Texture.Bind();

		const glm::mat4 LightModel = glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(0.2f)), LightPosition);
		m_LightSourceShader.SetUniform("u_MVP", m_ViewProjectionMatrix * LightModel);
		m_LightSourceShader.SetUniform("u_Color", glm::vec4(1.f));
		m_Program.SetUniform("u_Color", glm::vec4(1.f));
		m_Renderer.Draw(m_VertexArray, m_LightSourceShader, 36);

		m_Program.SetUniform("u_LightPosition", LightPosition);
		m_Program.SetUniform("u_ViewProjection", m_ViewProjectionMatrix);
		float angle = m_RotationAngle;
		for (auto& Position : CubePositions)
		{
			const glm::mat4 Model = glm::rotate(glm::translate(glm::mat4(1.f), Position), m_RotationAngle, glm::vec3(0.f, 1.f, 0.f));
			angle += 15.f;
			
			m_Program.SetUniform("u_NormalRot", glm::mat3(glm::transpose(glm::inverse(Model))));
			m_Program.SetUniform("u_Model", Model);
			m_Renderer.Draw(m_VertexArray, m_Program, 36);
		}
	}
}
