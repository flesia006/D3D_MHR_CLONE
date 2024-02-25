#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{
    objects = new M41Objects();

    terrain = new TerrainEditor();


    ball = new HalfSphere();    
    ball->Scale() *= 150000;
    ball->Pos().y -= 6000;
    //ball->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    ball->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/storm.tga");
    ball->UpdateWorld();

    fog = new Model("skydom");
    fog->SetTag("fog");
    fog->Scale() *= 100;
    fog->Pos().y -= 10000;
    fog->UpdateWorld();

    fieldFog = new Model("fog");
    fieldFog->Pos() = Vector3(2062.1f, 220, 17653.896f);
    fieldFog->Rot().y = XM_PI;
    fieldFog->UpdateWorld();

    player = new Player();
    player->Pos() = Vector3(2237.314, 460, 6411.237);

    garuk = new Garuk();
    garuk->SetTarget(player);

    valphalk = new Valphalk();
    valphalk->Pos().x = 2000;
    valphalk->Pos().z = 3000;
    valphalk->Rot().y += XM_PI;
    valphalk->UpdateWorld();
    valphalk->SetTarget(player);

    shadow = new Shadow();
    UIManager::Get();

    // 같이 알아보는 활용법 : 빛 호출 혹은 만들기 (<-빛 사용 방법)    
    light = Environment::Get()->GetLight(0);

    light->type = 0;
    light->pos = { 0, 3000, +3000 };
    light->range = 3000;

    light->direction = { -0.1, -1, 0.1 };
//    light->color = { 0.57, 0.66, 0.88, 1 }; // 밤조명
    light->color = { 1, 1, 1, 1 };        // 낮조명

    light->length;
    light->inner;   //조명 집중 범위 (빛이 집중되어 쏘이는 범위...의 비중)
    light->outer;   //조명 외곽 범위 (빛이 흩어져서 비치는 범위...의 비중)

    

    Sounds::Get()->AddSound("Valphalk_Thema", SoundPath + L"Valphalk_Thema.mp3",true);
    Sounds::Get()->Play("Valphalk_Thema", 0.03f);
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
    FOR(2) rasterizerState[i] = new RasterizerState();
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Additive();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE);

    AddSounds();
}

ShadowScene::~ShadowScene()
{
    delete garuk;
    delete objects;
    delete player;
    delete shadow;

}

void ShadowScene::Update()
{
    //if (KEY_DOWN('1')) light->type = 0;
    //if (KEY_DOWN('2')) light->type = 1;
    //if (KEY_DOWN('3')) light->type = 2;
    //if (KEY_DOWN('4')) light->type = 3;
    //terrain->Update();
    garuk->Update();
    //objects->Update();
    valphalk->Update();
    player->Update();
    fieldFog->UpdateWorld();
    
    ball->Rot().y += 0.02 * DELTA;
    ball->UpdateWorld();

    fog->Rot().y += 0.04 * DELTA;
    fog->UpdateWorld();
    
    UIManager::Get()->Update();

    if (player->getCollider()->IsCapsuleCollision(valphalk->GetCollider()[Valphalk::HEAD]))
    {
        UIManager::Get()->Hit(valphalk->damage);
    }
    if (KEY_PRESS('Z')) valphalk->curHP -= 1000;

}

void ShadowScene::PreRender()
{
    //그림자의 렌더 타겟 지정(및 준비)
    shadow->SetRenderTarget();

    //인간한테 뎁스 셰이더를 적용 (조건에 따른 셰이더 변화...등을 가진 조건 함수)
    objects->SetShader(L"Light/DepthMap.hlsl");
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    player->SetShader(L"Light/DepthMap.hlsl");
    garuk->SetShader(L"Light/DepthMap.hlsl");
    //조건에 따라 픽셀이 바뀐 인간을 렌더...해서 텍스처를 준비
    objects->Render();
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
    objects->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //셰이더가 세팅된 배경과 인간을 진짜 호출

    //terrain->Render();

    rasterizerState[1]->SetState(); // 후면도 그림
    {
        ball->Render();        
        valphalk->Render();
        objects->Render();
    }
    rasterizerState[0]->SetState();
    
    player->Render();
    garuk->Render();

    rasterizerState[1]->SetState();
    blendState[1]->SetState(); // 반투명
    {
        fog->Render();
        fieldFog->Render();
    }
    blendState[0]->SetState();
    rasterizerState[0]->SetState();

}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // 쿼드 출력용
    player->PostRender();
    UIManager::Get()->PostRender();
}

void ShadowScene::GUIRender()
{
      ball->GUIRender();
//    fog->GUIRender();
//    cloud->GUIRender();
//    cloud2->GUIRender();
//    cloud3->GUIRender();
//    cloud4->GUIRender();
//    forest->GUIRender();
//    terrain->GUIRender();
//    valphalk->GUIRender();
//    player->GUIRender(); // 디버그 조작용
    fieldFog->GUIRender();
    valphalk->GUIRender();
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
    // Valphalk
    // 포효
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"em086_05_vo_media_10.mp3");
    // 습격 부스터 가동
    sound->AddSound("em086_05_fx_media_25", SoundPath + L"em086_05_fx_media_25.mp3");
    // 습격 출발
    sound->AddSound("em086_05_fx_media_22", SoundPath + L"em086_05_fx_media_22.mp3");
    // 습격 비행중
    sound->AddSound("em086_05_fx_media_33", SoundPath + L"em086_05_fx_media_33.mp3");
    // 습격 낙하직전
    sound->AddSound("em086_05_fx_media_19", SoundPath + L"em086_05_fx_media_19.mp3");
    // 습격 낙하
    sound->AddSound("em086_05_fx_media_20", SoundPath + L"em086_05_fx_media_20.mp3");

    /////////////////////////////////////////////////////////////
    // Item
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
}
