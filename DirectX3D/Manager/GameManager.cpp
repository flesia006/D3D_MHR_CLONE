#include "Framework.h"

#include "Scenes/ModelExportScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/ParticleConfigScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/MapDesignScene.h"
#include "Scenes/ParticleScene.h"
#include "Scenes/SimpleTestScene.h"

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
#include "Scenes/OpeningScene.h"
#include "Scenes/LoadingScene.h"
#include <thread>
#include <chrono>
#include <future>
// ���� ����� ���� : ���� ��ƼŬ, �ٸ� Ư�� ��ƼŬ(��, ����ũ)
//                   + ���� ��ƼŬ ���� (�޸� Ŭ������ �߰���)
//                   + ��ƼŬ ���� ������ ��

// * ��ƼŬ ���� �� -> Ư��ȿ���� �߰��� �ʿ��ϰų�, Ȥ�� �׳� �����Ͻ� ���̶�...
//                    �׷� ��쿡 �ش��ϴ� �е��� �ٷ� �ѹ� �Ế�ô�.
void LoadScene();
void PlayScene();

GameManager::GameManager()
{
    Create();
    srand(static_cast<unsigned int>(time(NULL)));
    randN = (rand() % 3000) + 1000;

//    SceneManager::Get()->Create("ModelExport", new ModelExportScene());
//    SceneManager::Get()->Add("ModelExport");
//
//    SceneManager::Get()->Create("Grid", new GridScene());
//    SceneManager::Get()->Add("Grid");

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

//    SceneManager::Get()->Create("SimpleTestScene", new SimpleTestScene());
//    SceneManager::Get()->Add("SimpleTestScene");

//    SceneManager::Get()->Create("OpeningScene", new OpeningScene());    
//    SceneManager::Get()->Add("OpeningScene");
//
//    SceneManager::Get()->Create("LoadingScene", new LoadingScene());
//    SceneManager::Get()->Add("LoadingScene");

//    SceneManager::Get()->Add("Terrain");
//    CAM->isFreeCamTrue();

    // ���� ����ϰ� ���� ��� : CAM->isFreeCamTrue() ����� isLoading = false;�� ����
    // �ε��� ���� ����̶��  : CAM->isFreeComTrue() �츮�� isLoading = true; �� ����
    //CAM->isFreeCamTrue();
    UIManager::Get()->isLoading = false;
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

    std::promise<void> p;
    std::shared_future<void> start = p.get_future();

    //thread t1(LoadPlayScene, start);
    p.set_value();
    //t1.join();



    if (!isStart)
    {
        for (int key = 0; key < 256; key++) // � Ű�� �Է½� ����
        {
            if (GetAsyncKeyState(key) & 0x8000)            
                isStart = true;            
        }
    }

    if (UIManager::Get()->choice == 1 && isStart == true)
        LoadScene();
    if (UIManager::Get()->choice >= randN) // �������� �����ǰ� ��ڸ� �����ɸ�^^ // �������� �ε� ���ҽ� ����
        PlayScene();
    if (UIManager::Get()->choice == 6)
        exit(0);    
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
    sound->AddSound("queststart", SoundPath + L"queststart.mp3", false);
    sound->AddSound("uisound", SoundPath + L"UIsound.mp3", false);
    sound->AddSound("mapchangestart", SoundPath + L"mapchangestart.mp3", false);
    sound->AddSound("mapchangeend", SoundPath + L"mapchangeend.mp3", false);

    /////////////////////////////////////////////////////////////
    // UI
    sound->AddSound("gameStart", SoundPath + L"UI/Start.mp3", false);
    sound->AddSound("choice", SoundPath + L"UI/choice.mp3", false);
    sound->AddSound("select", SoundPath + L"UI/Select.mp3", false);
    sound->AddSound("back", SoundPath + L"UI/Back.mp3", false);
    sound->AddSound("playgame", SoundPath + L"UI/PlayGame.mp3", false);
    sound->AddSound("dontget", SoundPath + L"UI/dontGet.mp3", false);

    
    
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
    Sounds::Get()->AddSound("suwolstart", SoundPath + L"Player/suwolstart.mp3");
    Sounds::Get()->AddSound("suwolattack", SoundPath + L"Player/suwolattack.mp3");
    Sounds::Get()->AddSound("helmbreaker", SoundPath + L"Player/helmbreaker.mp3");


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
    // Ÿ���� 1,2,3
    sound->AddSound("hit_pl_media.bnk.2_14", SoundPath + L"hit_pl_media.bnk.2_14.mp3");
    sound->AddSound("hit_pl_media.bnk.2_20", SoundPath + L"hit_pl_media.bnk.2_20.mp3");
    sound->AddSound("hit_pl_media.bnk.2_35", SoundPath + L"hit_pl_media.bnk.2_35.mp3");
    // ��Ÿ
    sound->AddSound("hit_pl_media.bnk.2_38", SoundPath + L"hit_pl_media.bnk.2_38.mp3");

    /////////////////////////////////////////////////////////////
    // Valphalk
    // = Voice = 
    // ����
    sound->AddSound("em086_05_vo_media_7", SoundPath + L"Valphalk/em086_05_vo_media_7.mp3");
    // 
    // ��ȿ
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"Valphalk/em086_05_vo_media_10.mp3");
    // ��� ����
    sound->AddSound("em086_05_vo_media_20", SoundPath + L"Valphalk/em086_05_vo_media_20.mp3");
    // "�չ����"�� �������
    sound->AddSound("em086_05_vo_media_21", SoundPath + L"Valphalk/em086_05_vo_media_21.mp3");
    // DownBlast(�����ε��� ���� ����)
    sound->AddSound("em086_05_vo_media_14", SoundPath + L"Valphalk/em086_05_vo_media_14.mp3");
    // ���� ���� 1 �ƿ� (downblast ���� ��)
    sound->AddSound("em086_05_vo_media_1", SoundPath + L"Valphalk/em086_05_vo_media_1.mp3");
    // ���� ���� 4 (��� �غ�) (�չ������ "�������")
    sound->AddSound("em086_05_vo_media_4", SoundPath + L"Valphalk/em086_05_vo_media_4.mp3");
    // ���� ���� 5 ũ��
    sound->AddSound("em086_05_vo_media_5", SoundPath + L"Valphalk/em086_05_vo_media_5.mp3");
    // ���� ���� 6 ("�չ����")
    sound->AddSound("em086_05_vo_media_12", SoundPath + L"Valphalk/em086_05_vo_media_12.mp3");
    // �չ���� �� "�������"
    sound->AddSound("em086_05_vo_media_16", SoundPath + L"Valphalk/em086_05_vo_media_16.mp3");
    // �ް��� ��������
    sound->AddSound("em086_05_vo_media_18", SoundPath + L"Valphalk/em086_05_vo_media_18.mp3");
    // �ڵ������ ũ��
    sound->AddSound("em086_05_vo_media_23", SoundPath + L"Valphalk/em086_05_vo_media_23.mp3");
    // ���� ���̽�
    sound->AddSound("em086_05_vo_media_24", SoundPath + L"Valphalk/em086_05_vo_media_24.mp3");
    // �����
    sound->AddSound("em086_05_vo_media_25", SoundPath + L"Valphalk/em086_05_vo_media_25.mp3");
    // ���� �δ��
    sound->AddSound("em086_05_vo_media_26", SoundPath + L"Valphalk/em086_05_vo_media_26.mp3");
    // �Ұ���
    sound->AddSound("em086_05_vo_media_29", SoundPath + L"Valphalk/em086_05_vo_media_29.mp3");
    // ���
    sound->AddSound("em086_05_vo_media_30", SoundPath + L"Valphalk/em086_05_vo_media_30.mp3");

    // = SFX =     
    // ��� ����
    sound->AddSound("em086_05_fx_media_40", SoundPath + L"Valphalk/em086_05_fx_media_40.mp3");
    // ��� ��
    sound->AddSound("em086_05_fx_media_51", SoundPath + L"Valphalk/em086_05_fx_media_51.mp3");
    // ���� �ν��� ����
    sound->AddSound("em086_05_fx_media_25", SoundPath + L"Valphalk/em086_05_fx_media_25.mp3");
    // ���� ���
    sound->AddSound("em086_05_fx_media_22", SoundPath + L"Valphalk/em086_05_fx_media_22.mp3");
    // ���� ������
    sound->AddSound("em086_05_fx_media_33", SoundPath + L"Valphalk/em086_05_fx_media_33.mp3");
    // ���� ��������
    sound->AddSound("em086_05_fx_media_19", SoundPath + L"Valphalk/em086_05_fx_media_19.mp3");
    // ���� ����
    sound->AddSound("em086_05_fx_media_20", SoundPath + L"Valphalk/em086_05_fx_media_20.mp3");
    // ź�߻� ���� (6ź, downblast �� ������ ���� ġ���� �Ҹ�)
    sound->AddSound("em086_05_fx_media_32", SoundPath + L"Valphalk/em086_05_fx_media_32.mp3");    
    // ź�߻� ����
    sound->AddSound("em086_05_fx_media_50", SoundPath + L"Valphalk/em086_05_fx_media_50.mp3");
    sound->AddSound("em086_05_fx_media_50_2", SoundPath + L"Valphalk/em086_05_fx_media_50.mp3");
    // ���� ü��
    sound->AddSound("em086_05_fx_media_15", SoundPath + L"Valphalk/em086_05_fx_media_15.mp3");
    // ü���� ����
    sound->AddSound("em086_05_fx_media_5", SoundPath + L"Valphalk/em086_05_fx_media_5.mp3");
    // ���� �ڱ�
    sound->AddSound("em086_05_fx_media_30", SoundPath + L"Valphalk/em086_05_fx_media_30.mp3");
    // ���� ����
    sound->AddSound("em086_05_fx_media_35", SoundPath + L"Valphalk/em086_05_fx_media_35.mp3");
    sound->AddSound("em086_05_fx_media_35_2", SoundPath + L"Valphalk/em086_05_fx_media_35.mp3");
    // ���� ����
    sound->AddSound("em086_05_fx_media_24", SoundPath + L"Valphalk/em086_05_fx_media_24.mp3");
    // Ǯ����Ʈ ����
    sound->AddSound("em086_05_fx_media_41", SoundPath + L"Valphalk/em086_05_fx_media_41.mp3");
    sound->AddSound("em086_05_fx_media_3", SoundPath + L"Valphalk/em086_05_fx_media_3.mp3");
    sound->AddSound("em086_05_fx_media_11", SoundPath + L"Valphalk/em086_05_fx_media_11.mp3");


    // = SE = ( ������, ���� �Ҹ� ��)
    // �⺻ ���� ����
    sound->AddSound("em086_05_se_media_10", SoundPath + L"Valphalk/em086_05_se_media_10.mp3");
    sound->AddSound("em086_05_se_media_10_2", SoundPath + L"Valphalk/em086_05_se_media_10.mp3");
    // ���
    sound->AddSound("em086_05_se_media_20", SoundPath + L"Valphalk/em086_05_se_media_20.mp3");
    // ��� ������
    sound->AddSound("em086_05_se_media_32", SoundPath + L"Valphalk/em086_05_se_media_32.mp3");
    // ���� �ֵθ���
    sound->AddSound("em086_05_se_media_46", SoundPath + L"Valphalk/em086_05_se_media_46.mp3");


    
    /////////////////////////////////////////////////////////////
    // Item
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
    
    Sounds::Get()->AddSound("getWildBug", SoundPath + L"getWildBug.mp3");

    Sounds::Get()->AddSound("wheatstone1", SoundPath + L"wheatstone1.mp3");
    Sounds::Get()->AddSound("wheatstone2", SoundPath + L"wheatstone2.mp3");

    Sounds::Get()->AddSound("wirebug", SoundPath + L"Player/wirebug.mp3");

    Sounds::Get()->AddSound("capturing", SoundPath + L"pl_prop_media.bnk.2_81.mp3");
    Sounds::Get()->AddSound("capturing2", SoundPath + L"pl_prop_media.bnk.2_112.mp3");

    //UI
    Sounds::Get()->AddSound("Boxframe_select", SoundPath + L"UI/Boxframe_select.mp3");
    Sounds::Get()->AddSound("Boxitem_select", SoundPath + L"UI/Boxitem_select.mp3");
    Sounds::Get()->AddSound("Boxopen", SoundPath + L"UI/Boxopen.mp3");
    Sounds::Get()->AddSound("Icon_on", SoundPath + L"UI/Icon_on.mp3");
    Sounds::Get()->AddSound("Slot_move", SoundPath + L"UI/Slot_move.mp3");
    Sounds::Get()->AddSound("Slot_off", SoundPath + L"UI/Slot_off.mp3");
    Sounds::Get()->AddSound("Select", SoundPath + L"UI/Select.mp3");
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

void LoadPlayScene(std::shared_future<void> play)
{
    play.get();
    //SceneManager::Get()->Add("FightTestScene");
    return play.get();
}
void LoadScene() // ���� ���۽� �����׾� -> �ε������� ��ȯ
{
    SceneManager::Get()->Remove("OpeningScene");
    Sounds::Get()->Pause("lobbyBGM");
    SceneManager::Get()->Add("LoadingScene");
    UIManager::Get()->choice = 100;
}

void PlayScene(std::shared_future<void> play)
{
    play.get();
    SceneManager::Get()->Remove("LoadingScene");
    SceneManager::Get()->Add("FightTestScene");
    CAM->isFreeCamFalse();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return play.get();
}
void PlayScene() // �ε����� ����� ���ϴ� ������ �����Ѵ�.
{
    SceneManager::Get()->Remove("LoadingScene");
    //SceneManager::Get()->Add("PlayerTestScene");
    CAM->isFreeCamFalse();
    UIManager::Get()->isLoading = false;
}