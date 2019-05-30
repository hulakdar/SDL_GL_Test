#pragma once
#include "Test.h"

namespace TestSpace {

	class TestClearColor : public Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		virtual ~TestClearColor();

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}
