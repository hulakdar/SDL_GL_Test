#pragma once

#include "Test.h"
#include "Renderer.h"

namespace TestSpace {

	class Test3DBoxMany : public Test
	{
	protected:
		const Renderer&		m_Renderer;
		VertexBuffer		m_VertexBuffer;
		VertexBufferLayout	m_VertexBufferLayout;
		VertexArray			m_VertexArray;
		Shader				m_Program;
		Shader				m_LightSourceShader;
		Texture				m_Texture;
		glm::vec3			m_Translation;
		glm::mat4			m_ViewProjectionMatrix;
		float				m_RotationAngle;
	public:
		Test3DBoxMany(const Renderer& Renderer);
		virtual ~Test3DBoxMany() noexcept ;

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
	};

}
