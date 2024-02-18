#include "Framework.h"

#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/TerrainEditorScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/IntancingScene.h"
#include "Scenes/HumanScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/GBufferScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/AStarScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/BillboardScene.h"
#include "Scenes/ParticleScene.h"
#include "Scenes/ParticleConfigScene.h"
#include "Scenes/MirrorScene.h"
#include "Scenes/WaterScene.h"
#include "Scenes/QuadTreeScene.h"
#include "Scenes/TessellationScene.h"
#include "Scenes/TerrainLODScene.h"

// ���� ����� ���� : ���� ��ƼŬ, �ٸ� Ư�� ��ƼŬ(��, ����ũ)
//                   + ���� ��ƼŬ ���� (�޸� Ŭ������ �߰���)
//                   + ��ƼŬ ���� ������ ��

// * ��ƼŬ ���� �� -> Ư��ȿ���� �߰��� �ʿ��ϰų�, Ȥ�� �׳� �����Ͻ� ���̶�...
//                    �׷� ��쿡 �ش��ϴ� �е��� �ٷ� �ѹ� �Ế�ô�.

GameManager::GameManager()
{
    Create();

//    SceneManager::Get()->Create("ModelExport", new ModelExportScene());
//    SceneManager::Get()->Add("ModelExport");


    SceneManager::Get()->Create("ShadowScene", new ShadowScene());
    SceneManager::Get()->Add("ShadowScene");



//  SceneManager::Get()->Create("ParticleConfig", new ParticleConfigScene());
//  SceneManager::Get()->Add("ParticleConfig");

    SceneManager::Get()->Create("Grid", new GridScene());
    SceneManager::Get()->Add("Grid");

    //SceneManager::Get()->Create("Cube", new CubeScene());
    //SceneManager::Get()->Create("Sphere", new SphereScene());
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Create("Collision", new CollisionScene());
    //SceneManager::Get()->Create("ModelRender", new ModelRenderScene());
    //SceneManager::Get()->Create("ModelAnimationScene", new ModelAnimationScene());
    //SceneManager::Get()->Create("Instancing", new IntancingScene());
    //SceneManager::Get()->Create("HumanTest", new HumanScene());
    //SceneManager::Get()->Create("Game", new GameScene());
    //SceneManager::Get()->Create("RenderTarget", new RenderTargetScene());
    //SceneManager::Get()->Create("GeometryBuffer", new GBufferScene());
    //SceneManager::Get()->Create("ShadowScene", new ShadowScene());
    //SceneManager::Get()->Create("AStar", new AStarScene());
    //SceneManager::Get()->Create("LightTest", new LightScene());
    //SceneManager::Get()->Create("Billboard", new BillboardScene());
//    SceneManager::Get()->Create("Particle", new ParticleScene());
    // *�۾��� // SceneManager::Get()->Create("MirrorScene", new MirrorScene());
    //SceneManager::Get()->Create("WaterScene", new WaterScene());
    //SceneManager::Get()->Create("QuadTree", new QuadTreeScene());
    //SceneManager::Get()->Create("Tessellation", new TessellationScene());
    //SceneManager::Get()->Create("LOD", new TerrainLODScene());

    //SceneManager::Get()->Add("HumanTest");
    //SceneManager::Get()->Add("Game");
    //SceneManager::Get()->Add("RenderTarget");
    //SceneManager::Get()->Add("GeometryBuffer");
    //SceneManager::Get()->Add("ShadowScene");
    //SceneManager::Get()->Add("AStar");
    //SceneManager::Get()->Add("LightTest");
    //SceneManager::Get()->Add("Billboard");
    SceneManager::Get()->Add("Particle");
    //SceneManager::Get()->Add("MirrorScene");
    //SceneManager::Get()->Add("WaterScene");
    //SceneManager::Get()->Add("QuadTree");
    //SceneManager::Get()->Add("Tessellation");


}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();    

    SceneManager::Get()->Update();

    Environment::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

//    Font::Get()->SetColor("White");
//    Font::Get()->SetStyle("Default");
    
    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });
    
    static bool isActive = true;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    
    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("Default", L"Arial", 20, DWRITE_FONT_WEIGHT_MEDIUM);

    Font::Get()->AddColor("Black", 0, 0, 0);
    Font::Get()->AddStyle("Black", L"Arial", 30, DWRITE_FONT_WEIGHT_EXTRA_BLACK);

    Font::Get()->AddColor("Yellow", 1, 0.8, 0.1);
    Font::Get()->AddStyle("Yellow", L"Arial", 26, DWRITE_FONT_WEIGHT_MEDIUM);

    Font::Get()->AddColor("Gray", 0.9, 0.9, 0.9);
    Font::Get()->AddStyle("Gray", L"Arial", 26, DWRITE_FONT_WEIGHT_MEDIUM);
    
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}
