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

	//std::vector<VertexPositionUv3D> vertices;
	//std::vector<uint32_t> indices;
	//GeometryGenerator::CreateCube<VertexPositionUv3D>(Vec3f(2.0f, 2.0f, 2.0f), vertices, indices);

	//StaticMesh<VertexPositionUv3D>* mesh = RenderModule::CreateResource<StaticMesh<VertexPositionUv3D>>(vertices, indices);
	Shader* shader = RenderModule::CreateResource<Shader>("Resource/Shader/Shader.vert", "Resource/Shader/Shader.frag");
	TileMap* tileMap = RenderModule::CreateResource<TileMap>(TileMap::ESize::Size_512x512, TileMap::ESize::Size_128x128, Vec4f(1.0f, 0.0f, 0.0f, 1.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{		
			ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(200.0f, 200.0f));

			float windowWidth = ImGui::GetContentRegionAvail().x;
			float windowHeight = ImGui::GetContentRegionAvail().y;

			ImGui::Image((void*)(intptr_t)(tileMap->GetID()), ImVec2(windowWidth, windowHeight), ImVec2(0, 0), ImVec2(1, 1));
			ImGui::End();
			
			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			static float time = 0.0f;
			time += deltaSeconds;

			shader->Bind();
			{
				tileMap->Active(0);
				shader->SetUniform("model", Mat4x4::Scale(2.0f, 2.0f, 2.0f) * Mat4x4::RotateY(time));
				shader->SetUniform("view", Mat4x4::LookAt(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f)));
				shader->SetUniform("projection", Mat4x4::Perspective(
					MathModule::ToRadian(45.0f), 
					static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
					0.01f,
					100.0f
				));

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);

				//mesh->Bind();
				//glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
				//mesh->Unbind();
			}
			shader->Unbind();


			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}