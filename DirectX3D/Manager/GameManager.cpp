#include "Framework.h"

#include "Scenes/ModelExportScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/ParticleConfigScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/MapDesignScene.h"
#include "Scenes/ParticleScene.h"

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
#include "Scenes/NotUse/MirrorScene.h"
#include "Scenes/NotUse/WaterScene.h"
#include "Scenes/NotUse/QuadTreeScene.h"
#include "Scenes/NotUse/TessellationScene.h"
#include "Scenes/NotUse/TerrainLODScene.h"
#include "Scenes/ValphalkTestScene.h"
#include "Scenes/PlayerTestScene.h"
#include "Scenes/FightTestScene.h"


// 오늘 진행된 설명 : 궤적 파티클, 다른 특수 파티클(눈, 스파크)
//                   + 궤적 파티클 적용 (휴먼 클래스에 추가함)
//                   + 파티클 파일 설정용 씬

// * 파티클 설정 씬 -> 특수효과가 추가로 필요하거나, 혹은 그냥 복습하실 분이라도...
//                    그런 경우에 해당하는 분들은 바로 한번 써봅시다.

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


    SceneManager::Get()->Create("ValphalkTestScene", new ValphalkTestScene());
    SceneManager::Get()->Add("ValphalkTestScene");

//    SceneManager::Get()->Create("PlayerTestScene", new PlayerTestScene());
//    SceneManager::Get()->Add("PlayerTestScene");

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
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    SceneManager::Get()->PreRender();


    
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

    Font::Get()->AddColor("RealGray", 0.4, 0.4, 0.4);
    Font::Get()->AddStyle("RealGray", L"Arial", 26, DWRITE_FONT_WEIGHT_MEDIUM);
    
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
    sound->AddSound("questClear", SoundPath + L"quest_Clear.mp3", false);

    //sound->Play("Valphalk_Thema", 0.03f);
    sound->Play("env_114", .5f);
    /////////////////////////////////////////////////////////////
    // Player
    Sounds::Get()->AddSound("attack1", SoundPath + L"Player/attack1.mp3");
    Sounds::Get()->AddSound("attack2", SoundPath + L"Player/attack2.mp3");
    Sounds::Get()->AddSound("attack3", SoundPath + L"Player/attack3.mp3");
    Sounds::Get()->AddSound("attack4", SoundPath + L"Player/attack4.mp3");
    Sounds::Get()->AddSound("attack5", SoundPath + L"Player/attack5.mp3");
    Sounds::Get()->AddSound("big_hurt1", SoundPath + L"Player/big_hurt1.mp3");
    Sounds::Get()->AddSound("big_hurt2", SoundPath + L"Player/big_hurt2.mp3");
    Sounds::Get()->AddSound("breath1", SoundPath + L"Player/breath.mp3");
    Sounds::Get()->AddSound("breath2", SoundPath + L"Player/breath2.mp3");
    Sounds::Get()->AddSound("breath3", SoundPath + L"Player/breath3.mp3");
    Sounds::Get()->AddSound("clear", SoundPath + L"Player/clear.mp3");
    Sounds::Get()->AddSound("clear2", SoundPath + L"Player/clear_2.mp3");
    Sounds::Get()->AddSound("death", SoundPath + L"Player/death.mp3");
    Sounds::Get()->AddSound("eatting", SoundPath + L"Player/eatting.mp3");
    Sounds::Get()->AddSound("exhausted", SoundPath + L"Player/exhausted.mp3");
    Sounds::Get()->AddSound("hurt1", SoundPath + L"Player/hurt1.mp3");
    Sounds::Get()->AddSound("hurt2", SoundPath + L"Player/hurt2.mp3");
    Sounds::Get()->AddSound("hurt3", SoundPath + L"Player/hurt3.mp3");
    Sounds::Get()->AddSound("riding1", SoundPath + L"Player/riding1.mp3");
    Sounds::Get()->AddSound("riding2", SoundPath + L"Player/riding2.mp3");
    Sounds::Get()->AddSound("roll1", SoundPath + L"Player/roll.mp3");
    Sounds::Get()->AddSound("roll2", SoundPath + L"Player/roll2.mp3");
    Sounds::Get()->AddSound("roll3", SoundPath + L"Player/roll3.mp3");
    Sounds::Get()->AddSound("special1", SoundPath + L"Player/special_1.mp3");
    Sounds::Get()->AddSound("special2", SoundPath + L"Player/special_2.mp3");
    Sounds::Get()->AddSound("special3", SoundPath + L"Player/special_3.mp3");
    Sounds::Get()->AddSound("special4", SoundPath + L"Player/special_4.mp3");
    Sounds::Get()->AddSound("start", SoundPath + L"Player/start.mp3");
    Sounds::Get()->AddSound("igonan1", SoundPath + L"Player/igonan1.mp3");
    Sounds::Get()->AddSound("igonan2", SoundPath + L"Player/igonan2.mp3");



    /////////////////////////////////////////////////////////////
    // Weapon
    // 공격시검뽑는소리
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_5", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_5.mp3");
    // 기인베기성공사운드
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_8", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_8.mp3");
    // 납도사운드
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_9", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_9.mp3");
    // 공격시 검뽑는소리2
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_25", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_25.mp3");
    // 앉아발도기인베기 회피추가타
    sound->AddSound("pl_wp_l_swd_epv_media.bnk.2_8", SoundPath + L"pl_wp_l_swd_epv_media.bnk.2_8.mp3");
    // 검 휘두르는 바람소리
    sound->AddSound("pl_wp_l_swd_com_media.bnk.2_7", SoundPath + L"pl_wp_l_swd_com_media.bnk.2_7.mp3");

    /////////////////////////////////////////////////////////////
    // Valphalk
    // = Voice = 
    // 포효
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"Valphalk/em086_05_vo_media_10.mp3");
    // 흡기 사운드
    sound->AddSound("em086_05_vo_media_20", SoundPath + L"Valphalk/em086_05_vo_media_20.mp3");
    // DownBlast(옆으로돌아 측면 폭발)
    sound->AddSound("em086_05_vo_media_14", SoundPath + L"Valphalk/em086_05_vo_media_14.mp3");
    // 공격 사운드 1 아웅 (downblast 폭발 후)
    sound->AddSound("em086_05_vo_media_1", SoundPath + L"Valphalk/em086_05_vo_media_1.mp3");
    // 공격 사운드 4 (찌르기 준비) (앞발찍기후 "날개찍기")
    sound->AddSound("em086_05_vo_media_4", SoundPath + L"Valphalk/em086_05_vo_media_4.mp3");
    // 공격 사운드 5 크앙
    sound->AddSound("em086_05_vo_media_5", SoundPath + L"Valphalk/em086_05_vo_media_5.mp3");
    // 공격 사운드 6 ("앞발찍기")
    sound->AddSound("em086_05_vo_media_12", SoundPath + L"Valphalk/em086_05_vo_media_12.mp3");
    // 급강하 전방폭발
    sound->AddSound("em086_05_vo_media_18", SoundPath + L"Valphalk/em086_05_vo_media_18.mp3");
    // 대경직
    sound->AddSound("em086_05_vo_media_25", SoundPath + L"Valphalk/em086_05_vo_media_25.mp3");
    // 소경직
    sound->AddSound("em086_05_vo_media_29", SoundPath + L"Valphalk/em086_05_vo_media_29.mp3");
    // 사망
    sound->AddSound("em086_05_vo_media_30", SoundPath + L"Valphalk/em086_05_vo_media_30.mp3");

    // = SFX =     
    // 흡기 시작
    sound->AddSound("em086_05_fx_media_40", SoundPath + L"Valphalk/em086_05_fx_media_40.mp3");
    // 흡기 끝
    sound->AddSound("em086_05_fx_media_51", SoundPath + L"Valphalk/em086_05_fx_media_51.mp3");
    // 습격 부스터 가동
    sound->AddSound("em086_05_fx_media_25", SoundPath + L"Valphalk/em086_05_fx_media_25.mp3");
    // 습격 출발
    sound->AddSound("em086_05_fx_media_22", SoundPath + L"Valphalk/em086_05_fx_media_22.mp3");
    // 습격 비행중
    sound->AddSound("em086_05_fx_media_33", SoundPath + L"Valphalk/em086_05_fx_media_33.mp3");
    // 습격 낙하직전
    sound->AddSound("em086_05_fx_media_19", SoundPath + L"Valphalk/em086_05_fx_media_19.mp3");
    // 습격 낙하
    sound->AddSound("em086_05_fx_media_20", SoundPath + L"Valphalk/em086_05_fx_media_20.mp3");
    // 탄발사 차지 (6탄, downblast 등 차지에 쓰임 치지직 소리)
    sound->AddSound("em086_05_fx_media_32", SoundPath + L"Valphalk/em086_05_fx_media_32.mp3");    
    // 탄발사 사운드
    sound->AddSound("em086_05_fx_media_50", SoundPath + L"Valphalk/em086_05_fx_media_50.mp3");
    sound->AddSound("em086_05_fx_media_50_2", SoundPath + L"Valphalk/em086_05_fx_media_50.mp3");
    // 공중 체공
    sound->AddSound("em086_05_fx_media_15", SoundPath + L"Valphalk/em086_05_fx_media_15.mp3");
    // 체공중 돌진
    sound->AddSound("em086_05_fx_media_5", SoundPath + L"Valphalk/em086_05_fx_media_5.mp3");
    // 냅다 박기
    sound->AddSound("em086_05_fx_media_30", SoundPath + L"Valphalk/em086_05_fx_media_30.mp3");
    // 폭발 사운드
    sound->AddSound("em086_05_fx_media_35", SoundPath + L"Valphalk/em086_05_fx_media_35.mp3");


    // = SE = ( 폭발음, 걸음 소리 등)
    // 기본 폭발 사운드
    sound->AddSound("em086_05_se_media_10", SoundPath + L"Valphalk/em086_05_se_media_10.mp3");
    sound->AddSound("em086_05_se_media_10_2", SoundPath + L"Valphalk/em086_05_se_media_10.mp3");
    // 찌르기
    sound->AddSound("em086_05_se_media_20", SoundPath + L"Valphalk/em086_05_se_media_20.mp3");
    // 찌르고 돌리기
    sound->AddSound("em086_05_se_media_32", SoundPath + L"Valphalk/em086_05_se_media_32.mp3");
    // 날개 휘두르기
    sound->AddSound("em086_05_se_media_46", SoundPath + L"Valphalk/em086_05_se_media_46.mp3");


    
    /////////////////////////////////////////////////////////////
    // Item
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
    
    Sounds::Get()->AddSound("getWildBug", SoundPath + L"getWildBug.mp3");

    Sounds::Get()->AddSound("wheatstone1", SoundPath + L"wheatstone1.mp3");
    Sounds::Get()->AddSound("wheatstone2", SoundPath + L"wheatstone2.mp3");

    Sounds::Get()->AddSound("wirebug", SoundPath + L"Player/wirebug.mp3");


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
