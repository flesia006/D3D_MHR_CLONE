#include "Framework.h"

#include "Scenes/ModelExportScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/ParticleConfigScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/MapDesignScene.h"

#include "Scenes/NotUse/CubeScene.h"
#include "Scenes/NotUse/SphereScene.h"
#include "Scenes/NotUse/TerrainEditorScene.h"
#include "Scenes/NotUse/CollisionScene.h"
#include "Scenes/NotUse/ModelRenderScene.h"
#include "Scenes/NotUse/ModelAnimationScene.h"
#include "Scenes/NotUse/IntancingScene.h"
#include "Scenes/NotUse/HumanScene.h"
#include "Scenes/NotUse/GameScene.h"
#include "Scenes/NotUse/RenderTargetScene.h"
#include "Scenes/NotUse/GBufferScene.h"
#include "Scenes/NotUse/AStarScene.h"
#include "Scenes/NotUse/LightScene.h"
#include "Scenes/NotUse/BillboardScene.h"
#include "Scenes/NotUse/ParticleScene.h"
#include "Scenes/NotUse/MirrorScene.h"
#include "Scenes/NotUse/WaterScene.h"
#include "Scenes/NotUse/QuadTreeScene.h"
#include "Scenes/NotUse/TessellationScene.h"
#include "Scenes/NotUse/TerrainLODScene.h"
#include "Scenes/ValphalkTestScene.h"
#include "Scenes/PlayerTestScene.h"
#include "Scenes/FightTestScene.h"


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
//
    SceneManager::Get()->Create("Grid", new GridScene());
    SceneManager::Get()->Add("Grid");


//    SceneManager::Get()->Create("ShadowScene", new ShadowScene());
//    SceneManager::Get()->Add("ShadowScene");
//    SceneManager::Get()->Create("MapDesignScene", new MapDesignScene());
//    SceneManager::Get()->Add("MapDesignScene");
//      SceneManager::Get()->Create("Particle", new ParticleScene());
//      SceneManager::Get()->Add("Particle");
//    SceneManager::Get()->Create("ParticleConfig", new ParticleConfigScene());
//    SceneManager::Get()->Add("ParticleConfig");


//    SceneManager::Get()->Create("ValphalkTestScene", new ValphalkTestScene());
//    SceneManager::Get()->Add("ValphalkTestScene");

   SceneManager::Get()->Create("PlayerTestScene", new PlayerTestScene());
   SceneManager::Get()->Add("PlayerTestScene");

//   SceneManager::Get()->Create("FightTestScene", new FightTestScene());
//   SceneManager::Get()->Add("FightTestScene");

//    SceneManager::Get()->Add("Terrain");


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

    auto sound = Sounds::Get();
    // Sounds::Get()->AddSound("", SoundPath + L".mp3");
    // Sounds::Get()->Play("", .5f);
    /////////////////////////////////////////////////////////////
    // BGM
    sound->AddSound("Valphalk_Thema", SoundPath + L"Valphalk_Thema.mp3", true);
    sound->AddSound("env_114", SoundPath + L"env_114.mp3", true);

    sound->Play("Valphalk_Thema", 0.03f);
    sound->Play("env_114", .5f);
    /////////////////////////////////////////////////////////////
    // Player
    Sounds::Get()->AddSound("attack1", SoundPath + L"Player/attack1.mp3");
    Sounds::Get()->AddSound("attack2", SoundPath + L"Player/attack2.mp3");
    Sounds::Get()->AddSound("attack3", SoundPath + L"Player/attack3.mp3");
    Sounds::Get()->AddSound("attack4", SoundPath + L"Player/attack4.mp3");
    Sounds::Get()->AddSound("attack5", SoundPath + L"Player/attack5.mp3");
    Sounds::Get()->AddSound("special1", SoundPath + L"Player/special_1.mp3");
    Sounds::Get()->AddSound("special2", SoundPath + L"Player/special_2.mp3");
    Sounds::Get()->AddSound("special3", SoundPath + L"Player/special_3.mp3");
    Sounds::Get()->AddSound("special4", SoundPath + L"Player/special_4.mp3");
    


    /////////////////////////////////////////////////////////////
    // Weapon
    // ���ݽð˻̴¼Ҹ�
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_5", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_5.mp3");
    // ���κ��⼺������
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_8", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_8.mp3");
    // ��������
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_9", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_9.mp3");
    // ���ݽ� �˻̴¼Ҹ�2
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_25", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_25.mp3");
    // �ɾƹߵ����κ��� ȸ���߰�Ÿ
    sound->AddSound("pl_wp_l_swd_epv_media.bnk.2_8", SoundPath + L"pl_wp_l_swd_epv_media.bnk.2_8.mp3");
    // �� �ֵθ��� �ٶ��Ҹ�
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_7", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_7.mp3");

    /////////////////////////////////////////////////////////////
    // Valphalk
    // = Voice = 
    // ��ȿ
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"em086_05_vo_media_10.mp3");
    // ��� ����
    sound->AddSound("em086_05_vo_media_20", SoundPath + L"em086_05_vo_media_20.mp3");
    // DownBlast(�����ε��� ���� ����)
    sound->AddSound("em086_05_vo_media_14", SoundPath + L"em086_05_vo_media_14.mp3");
    // ���� ���� 1 �ƿ� (downblast ���� ��)
    sound->AddSound("em086_05_vo_media_1", SoundPath + L"em086_05_vo_media_1.mp3");
    // ���� ���� 4 (��� �غ�)
    sound->AddSound("em086_05_vo_media_1", SoundPath + L"em086_05_vo_media_4.mp3");
    // ���� ���� 5 ũ��
    sound->AddSound("em086_05_vo_media_5", SoundPath + L"em086_05_vo_media_5.mp3");

    // = SFX =     
    // ��� ����
    sound->AddSound("em086_05_fx_media_40", SoundPath + L"em086_05_fx_media_40.mp3");
    // ��� ��
    sound->AddSound("em086_05_fx_media_51", SoundPath + L"em086_05_fx_media_51.mp3");
    // ���� �ν��� ����
    sound->AddSound("em086_05_fx_media_25", SoundPath + L"em086_05_fx_media_25.mp3");
    // ���� ���
    sound->AddSound("em086_05_fx_media_22", SoundPath + L"em086_05_fx_media_22.mp3");
    // ���� ������
    sound->AddSound("em086_05_fx_media_33", SoundPath + L"em086_05_fx_media_33.mp3");
    // ���� ��������
    sound->AddSound("em086_05_fx_media_19", SoundPath + L"em086_05_fx_media_19.mp3");
    // ���� ����
    sound->AddSound("em086_05_fx_media_20", SoundPath + L"em086_05_fx_media_20.mp3");
    // ź�߻� ���� (6ź, downblast �� ������ ����)
    sound->AddSound("em086_05_fx_media_32", SoundPath + L"em086_05_fx_media_32.mp3");    
    // ź�߻� ����
    sound->AddSound("em086_05_fx_media_50", SoundPath + L"em086_05_fx_media_50.mp3");
    sound->AddSound("em086_05_fx_media_50_2", SoundPath + L"em086_05_fx_media_50.mp3");

    // = SE = ( ������, ���� �Ҹ� ��)
    // �⺻ ���� ����
    sound->AddSound("em086_05_se_media_10", SoundPath + L"em086_05_se_media_10.mp3");
    sound->AddSound("em086_05_se_media_10_2", SoundPath + L"em086_05_se_media_10.mp3");
    // ���
    sound->AddSound("em086_05_se_media_20", SoundPath + L"em086_05_se_media_20.mp3");
    // ��� ������
    sound->AddSound("em086_05_se_media_32", SoundPath + L"em086_05_se_media_32.mp3");


    
    /////////////////////////////////////////////////////////////
    // Item
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
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
