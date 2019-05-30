#pragma once

#include "Test.h"
#include "Renderer.h"

namespace TestSpace {

	class Test3DBox : public Test
	{
	protected:
		const Renderer&		m_Renderer;
		VertexBuffer		m_VertexBuffer;
		IndexBuffer			m_IndexBuffer;
		VertexBufferLayout	m_VertexBufferLayout;
		VertexArray			m_VertexArray;
		Shader				m_Program;
		Texture				m_Texture;
		glm::mat4			m_Model;
		glm::vec3			m_Translation;
		float				m_RotationAngle;
	public:
		Test3DBox(const Renderer& Renderer);
		virtual ~Test3DBox();

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}
