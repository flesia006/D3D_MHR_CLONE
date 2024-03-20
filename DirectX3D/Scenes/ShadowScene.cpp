#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{    
    objects = new M41Objects();
    objects2 = new M42Objects();
    terrain = new TerrainEditor();
    ball = new HalfSphere();
    fog = new Model("skydom");
    fieldFog = new Model("fog");
    player = new Player();
    valphalk = new Valphalk();
    garuk = new Sample();
    wireBug = new WireBug();


    ball->Scale() *= 150000;
    ball->Pos().y -= 6000;
    //ball->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    ball->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/storm.tga");
    ball->UpdateWorld();

    fog->SetTag("fog");
    fog->Scale() *= 100;
    fog->Pos().y -= 10000;
    fog->UpdateWorld();

    fieldFog->Pos() = Vector3(2062.1f, 220, 17653.896f);
    fieldFog->Rot().y = XM_PI;
    fieldFog->UpdateWorld();

    
    //player->Pos() = Vector3(2237.314, 460, 6411.237);
    player->Pos() = Vector3(632, 10, 2000);
    player->Rot().y = XM_PIDIV2;
    player->SetDog(garuk);
    player->SetTerrain(terrain);
    player->SetValphalk(valphalk);
    player->SetWireBug(wireBug);

    valphalk->Pos().x = 2000;
    valphalk->Pos().z = 3000;
    valphalk->Rot().y += XM_PI;
    valphalk->UpdateWorld();
    valphalk->SetTarget(player);
    valphalk->SetTerrain(terrain);

    garuk->SetTarget(player);
    garuk->SetEnemy(valphalk);
    garuk->SetTerrain(terrain);

    wireBug->Pos() = { 2010,390,4900 };

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


    //Sounds::Get()->AddSound("Valphalk_Thema", SoundPath + L"Valphalk_Thema.mp3",true);
    //Sounds::Get()->Play("Valphalk_Thema", 0.03f);
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
    FOR(2) rasterizerState[i] = new RasterizerState();
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Additive();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

ShadowScene::~ShadowScene()
{
    delete garuk;
    delete objects;
    delete objects2;
    delete player;
    delete shadow;
    delete valphalk;
    delete ball;
    delete fog;
    delete terrain;
    delete wireBug;
}

void ShadowScene::Update()
{
    //if (KEY_DOWN('1')) light->type = 0;
    //if (KEY_DOWN('2')) light->type = 1;
    //if (KEY_DOWN('3')) light->type = 2;
    //if (KEY_DOWN('4')) light->type = 3;
    //terrain->Update();
    if (UI->isMapChange == false) // 시작맵
    {
        player->Pos().y = 10;
        garuk->Pos().y = 10;
        objects2->Update();
    }
    else // 전투맵
    {
        wireBug->Update();
        objects->Update();
        valphalk->Update();
    }
    //valphalk->Update();
    player->Update();
    garuk->Update();
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

    if (KEY_DOWN('P'))
        UI->isMapChange = false;
    if (KEY_DOWN('L'))
        UI->isMapChange = true;

}

void ShadowScene::PreRender()
{
    //그림자의 렌더 타겟 지정(및 준비)
    //shadow->SetRenderTarget();

    ////인간한테 뎁스 셰이더를 적용 (조건에 따른 셰이더 변화...등을 가진 조건 함수)
    //objects->SetShader(L"Light/DepthMap.hlsl");
    //valphalk->SetShader(L"Light/DepthMap.hlsl");
    //player->SetShader(L"Light/DepthMap.hlsl");
    //garuk->SetShader(L"Light/DepthMap.hlsl");
    ////조건에 따라 픽셀이 바뀐 인간을 렌더...해서 텍스처를 준비
    //objects->Render();
    //objects2->Render();
    //valphalk->Render();
    ////player->Render();
    //
    //garuk->Render();    
    player->PreRender();
    
}

void ShadowScene::Render()
{
    //skyBox->Render();

    //위 함수에서 만들어진 텍스처를 그림자에서 렌더 대상으로 세팅
    shadow->SetRender();
    if (firstRender == false)
    {
        valphalk->Render();
        objects->Render();
        firstRender = true;
    }

    //그림자를 받기 위한 셰이더 세팅
    objects->SetShader(L"Light/Shadow.hlsl");
    objects2->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //셰이더가 세팅된 배경과 인간을 진짜 호출

    //terrain->Render();

    rasterizerState[1]->SetState(); // 후면도 그림
    {
        ball->Render();        
        if (UI->isMapChange == false) // 시작맵
        {
            objects2->Render();
        }
        else // 전투맵
        {
            wireBug->Render();
            valphalk->Render();
            objects->Render();
        }
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
        
    ItemManager::Get()->Render();
}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // 쿼드 출력용
    player->PostRender();
    wireBug->PostRender();
    garuk->PostRender();
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
      
    player->GUIRender(); // 디버그 조작용
    fieldFog->GUIRender();
    valphalk->GUIRender();
    CAM->GUIRender();
    UIManager::Get()->GUIRender();
    ItemManager::Get()->GUIRender();
    //player->GUIRender(); // 디버그 조작용
    //UIManager::Get()->GUIRender();
}
