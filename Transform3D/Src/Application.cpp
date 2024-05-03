#include "GeometryRenderer3D.h"
#include "MeshRenderer.h"

#include "Application.h"
#include "EntityManager.h"
#include "Grid.h"
#include "Sphere.h"

Application::Application()
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
}

Application::~Application()
{
	EntityManager::Get().Shutdown();

	PlatformModule::Uninit();
	CrashModule::Uninit();
}

void Application::Init()
{
	geometryRenderer_ = RenderModule::CreateResource<GeometryRenderer3D>();
	meshRenderer_ = RenderModule::CreateResource<MeshRenderer>();

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);
	float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

	Mat4x4 view = Mat4x4::LookAt(Vec3f(0.0f, 5.0f, 10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	Mat4x4 proj = Mat4x4::Perspective(PiDiv4, aspect, 0.01f, 100.0f);

	geometryRenderer_->SetView(view);
	geometryRenderer_->SetProjection(proj);

	meshRenderer_->SetView(view);
	meshRenderer_->SetProjection(proj);

	EntityManager::Get().Startup();

	entities_ = 
	{
		EntityManager::Get().CreateEntity<Grid>(geometryRenderer_),
		EntityManager::Get().CreateEntity<Sphere>(meshRenderer_),
	};
}

void Application::Run()
{
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			for (auto entity : entities_)
			{
				entity->Tick(deltaSeconds);
			}

			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.3f, 0.3f, 0.3f, 1.0f);

			for (auto entity : entities_)
			{
				entity->Render();
			}

			RenderModule::EndFrame();
		}
	);
}