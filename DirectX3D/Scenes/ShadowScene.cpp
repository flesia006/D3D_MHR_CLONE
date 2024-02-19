#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{
    forest = new Model("GroundAll(fix)");
    forest->Pos() += Vector3::Back() * 16000;
    forest->UpdateWorld();

    skyDom = new Model("SkyDom");
    skyDom->Scale() *= 100;
    skyDom->Pos().y -= 25000;
    skyDom->UpdateWorld();

    garuk = new Garuk();
    valphalk = new Valphalk();
    valphalk->Pos().z -= 1500.0f;
    valphalk->Rot().y += XM_PI;
    valphalk->UpdateWorld();

    player = new Player();
    shadow = new Shadow();
    UIManager::Get();

    // 같이 알아보는 활용법 : 빛 호출 혹은 만들기 (<-빛 사용 방법)    
    light = Environment::Get()->GetLight(0);

    light->type = 0;
    light->pos = { 0, 3000, +3000 };
    light->range = 3000;

    light->direction = { -0.1, -1, 0.1 };
    light->color = { 1, 1, 1, 1 };

    light->length;
    light->inner;   //조명 집중 범위 (빛이 집중되어 쏘이는 범위...의 비중)
    light->outer;   //조명 외곽 범위 (빛이 흩어져서 비치는 범위...의 비중)

    skyBox = new SkyBox(L"Textures/Landscape/Texture3.dds");


    FOR(2) rasterizerSatate[i] = new RasterizerState();
    rasterizerSatate[1]->CullMode(D3D11_CULL_NONE);

    AddSounds();
}

ShadowScene::~ShadowScene()
{
    delete garuk;
    delete forest;
    delete player;
    delete shadow;
    delete skyBox;

}

void ShadowScene::Update()
{
    //if (KEY_DOWN('1')) light->type = 0;
    //if (KEY_DOWN('2')) light->type = 1;
    //if (KEY_DOWN('3')) light->type = 2;
    //if (KEY_DOWN('4')) light->type = 3;
    garuk->SetTarget(player);
    garuk->Update();
    forest->UpdateWorld();
    valphalk->Update();
    player->Update();
    skyDom->Rot().y += 0.025 * DELTA;
    skyDom->UpdateWorld();
    UIManager::Get()->Update();

    if (player->getCollider()->IsCapsuleCollision(valphalk->GetCollider()[Valphalk::HEAD]))
    {
        UIManager::Get()->Hit(valphalk->damage);
    }
}

void ShadowScene::PreRender()
{
    //그림자의 렌더 타겟 지정(및 준비)
    shadow->SetRenderTarget();

    //인간한테 뎁스 셰이더를 적용 (조건에 따른 셰이더 변화...등을 가진 조건 함수)
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    player->SetShader(L"Light/DepthMap.hlsl");
    garuk->SetShader(L"Light/DepthMap.hlsl");
    //조건에 따라 픽셀이 바뀐 인간을 렌더...해서 텍스처를 준비
    valphalk->Render();
    player->Render();
    garuk->Render();
}

void ShadowScene::Render()
{
    //skyBox->Render();

    //위 함수에서 만들어진 텍스처를 그림자에서 렌더 대상으로 세팅
    shadow->SetRender();


    //그림자를 받기 위한 셰이더 세팅
    forest->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //셰이더가 세팅된 배경과 인간을 진짜 호출

    rasterizerSatate[1]->SetState();
    {
        forest->Render();
        valphalk->Render();
        skyDom->Render();
    }
    rasterizerSatate[0]->SetState();
    player->Render();
    garuk->Render();

}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // 쿼드 출력용
    player->PostRender();
    UIManager::Get()->PostRender();
}

void ShadowScene::GUIRender()
{
    skyDom->GUIRender();
    //valphalk->GUIRender();
    //player->GUIRender(); // 디버그 조작용
    //UIManager::Get()->GUIRender();
}

void ShadowScene::AddSounds()
{    
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
    Sounds::Get()->AddSound("Heeee", SoundPath + L"Heeee.mp3");
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
    // Item
    sound->AddSound("health_potion", SoundPath + L"health_potion.mp3");

    /////////////////////////////////////////////////////////////
    // Valphalk
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"em086_05_vo_media_10.mp3");

}
