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
#include "Quat.h"
#include "Transform.h"

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
	GeometryRenderer3D* renderer = RenderModule::CreateResource<GeometryRenderer3D>();
	TileMap* tileMap = RenderModule::CreateResource<TileMap>(TileMap::ESize::Size_512x512, TileMap::ESize::Size_128x128, Vec4f(1.0f, 0.0f, 0.0f, 1.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);
	float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

	Mat4x4 view = Mat4x4::LookAt(Vec3f(0.0f, 5.0f, 10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	Mat4x4 proj = Mat4x4::Perspective(MathModule::ToRadian(45.0f), aspect, 0.01f, 100.0f);
	
	renderer->SetView(view);
	renderer->SetProjection(proj);
	
	Vec3f position = Vec3f(0.0f, 0.0f, 0.0f);

	Vec3f axis = Vec3f(0.0f, 0.0f, 0.0f);
	float radian = 0.0f;

	Vec3f scale = Vec3f(1.0f, 1.0f, 1.0f);

	Transform transform;

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));

			ImGui::Text("Position");
			ImGui::Text("position");
			ImGui::SameLine();
			ImGui::SliderFloat3("##position", position.data, -10.0f, 10.0f);
			ImGui::SameLine();
			if (ImGui::Button("Reset##position"))
			{
				position = Vec3f(0.0f, 0.0f, 0.0f);
			}
			ImGui::Separator();

			ImGui::Text("Rotate");
			ImGui::Text("%-6s", "axis");
			ImGui::SameLine();
			ImGui::SliderFloat3("##axis", axis.data, -1.0f, 1.0f);
			ImGui::SameLine();
			if (ImGui::Button("Reset##axis"))
			{
				axis = Vec3f(0.0f, 0.0f, 0.0f);
			}

			ImGui::Text("%-6s", "radian");
			ImGui::SameLine();
			ImGui::SliderFloat("##radian", &radian, -TwoPi, TwoPi);
			ImGui::SameLine();
			if (ImGui::Button("Reset##radian"))
			{
				radian = 0.0f;
			}

			ImGui::Separator();

			ImGui::Text("Scale");
			ImGui::Text("scale");
			ImGui::SameLine();
			ImGui::SliderFloat3("##scale", scale.data, 0.0f, 10.0f);
			ImGui::SameLine();
			if (ImGui::Button("Reset##scale"))
			{
				scale = Vec3f(1.0f, 1.0f, 1.0f);
			}

			ImGui::End();
			
			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.3f, 0.3f, 0.3f, 1.0f);

			renderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			transform.position = position;
			transform.rotate = Quat::AxisRadian(axis, radian);
			transform.scale = scale;

			renderer->DrawCube3D(Mat4x4::Identity(), Vec3f(2.0f, 2.0f, 2.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
			shader->Bind();
			{
				tileMap->Active(0);

				shader->SetUniform("world", Transform::ToMat(transform));
				shader->SetUniform("view", view);
				shader->SetUniform("projection", proj);

				mesh->Bind();
				glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
				mesh->Unbind();
			}
			shader->Unbind();
	
			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}