#include <cstdint>
#include <Windows.h>

#include <glad/glad.h>
#include <imgui.h>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"
#include "Shader.h"
#include "TileMap.h"

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

	TileMap* tileMap = RenderModule::CreateResource<TileMap>(TileMap::ESize::Size_512x512, TileMap::ESize::Size_32x32);

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{		
			ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(600.0f, 600.0f));

			float windowWidth = ImGui::GetContentRegionAvail().x; // 창의 너비를 얻습니다.
			float windowHeight = ImGui::GetContentRegionAvail().y; // 창의 높이를 얻습니다.

			ImGui::Image((void*)(intptr_t)(tileMap->GetID()), ImVec2(windowWidth, windowHeight), ImVec2(0, 0), ImVec2(1, 1));
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