#include <cstdint>
#include <Windows.h>

#include <glad/glad.h>
#include <imgui.h>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"
#include "Shader.h"
#include "TileMap.h"
#include "Vertex3D.h"
#include "GeometryGenerator.h"
#include "GeometryRenderer3D.h"
#include "StaticMesh.h"

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

	std::vector<VertexPositionNormalUv3D> vertices;
	std::vector<uint32_t> indices;
	GeometryGenerator::CreateCube(Vec3f(2.0f, 2.0f, 2.0f), vertices, indices);

	StaticMesh<VertexPositionNormalUv3D>* mesh = RenderModule::CreateResource<StaticMesh<VertexPositionNormalUv3D>>(vertices, indices);
	Shader* shader = RenderModule::CreateResource<Shader>("Resource/Shader/Shader.vert", "Resource/Shader/Shader.frag");
	GeometryRenderer3D* renderer = RenderModule::CreateResource< GeometryRenderer3D>();
	TileMap* tileMap = RenderModule::CreateResource<TileMap>(TileMap::ESize::Size_512x512, TileMap::ESize::Size_128x128, Vec4f(1.0f, 0.0f, 0.0f, 1.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);
	float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
	
	Vec3f extensions = Vec3f(1.0f, 1.0f, 1.0f);
	Vec4f color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	renderer->SetView(Mat4x4::LookAt(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f)));
	renderer->SetProjection(Mat4x4::Perspective(MathModule::ToRadian(45.0f), aspect, 0.01f, 100.0f));

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{		
			ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(400.0f, 100.0f));
			ImGui::SliderFloat3("extensions", extensions.data, 0.0f, 3.0f);
			ImGui::ColorEdit4("color", color.data);
			ImGui::End();
			
			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.3f, 0.3f, 0.3f, 1.0f);

			static float time = 0.0f;
			time += deltaSeconds;

			renderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);
			renderer->DrawCube3D(Mat4x4::RotateZ(time), extensions, color);
			
			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}