#pragma once
#include <imgui/imgui.h>

namespace TestSpace {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() noexcept {}

		virtual void OnUpdate(float DeltaTime) {
			(void)DeltaTime;
		}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
}

