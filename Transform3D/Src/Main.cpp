#include <cstdint>
#include <Windows.h>

#include <imgui.h>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	PlatformModule::WindowConstructParams windowParam{ L"Transform3D", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);

	HWND hwnd = PlatformModule::GetWindowHandle();
	RenderModule::Init(hwnd);

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	RenderModule::SetPointSizeMode(true);
	RenderModule::SetAlphaBlendMode(true);
	RenderModule::SetDepthMode(true);

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{		
			ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(800.0f, 600.0f));
			ImGui::End();
			
			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}