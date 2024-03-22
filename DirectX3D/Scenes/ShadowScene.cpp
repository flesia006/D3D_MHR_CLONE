#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{    
    //objects = new M41Objects();
    objects2 = new M42Objects();
    terrain = new TerrainEditor();
    player = new Player();
    valphalk = new Valphalk();
    garuk = new Sample();
    wireBug = new WireBug();

    //player->Pos() = Vector3(2237.314, 460, 6411.237);
    player->Pos() = Vector3(532, 10, 2900);
    player->GetMaterials()[7]->SetShader(L"Model/ModelAnimation2.hlsl");
    player->GetMaterials()[9]->SetShader(L"Model/ModelAnimation2.hlsl");
    player->Rot().y = XM_PI;
    player->SetGaruk(garuk->GetRealPos());
    player->SetDog(garuk);
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

    wireBug->Pos() = { 2010,310,4900 };

    shadow = new Shadow();
    UIManager::Get();

    ball = new HalfSphere(1, 360, 5);
    ball->Scale() *= 500000;
    ball->Pos().y -= 6000;
    ball->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    ball->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/sky.tga");
    ball->UpdateWorld();

    ball2 = new HalfSphere(1, 360, 5);
    ball2->Scale() *= 500000;
    ball2->Rot().x += XM_PI;
    ball2->Rot().y += XM_PI;
    ball2->Pos().y -= 6000;
    ball2->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    ball2->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/sky.tga");
    ball2->UpdateWorld();


    fog = new HalfSphere(1, 360, 5);
    fog->Scale() *= 50000;
    fog->Pos().y -= 500;
    fog->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    fog->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/newcloud2.png");
    fog->UpdateWorld();

    fog2 = new HalfSphere(1, 360, 5);
    fog2->Scale() *= 30000;
    fog2->Pos().y -= 500;
    fog2->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    fog2->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/newcloud2.png");
    fog2->UpdateWorld();

    fogRe = new HalfSphere(1, 360, 5);
    fogRe->Scale() *= 50000;
    fogRe->Rot().x += XM_PI;
    fogRe->Rot().y += XM_PI;
    fogRe->Pos().y -= 500;
    fogRe->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    fogRe->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/newcloud2.png");
    fogRe->UpdateWorld();

    fog2Re = new HalfSphere(1, 360, 5);
    fog2Re->Scale() *= 30000;
    fog2Re->Rot().x += XM_PI;
    fog2Re->Rot().y += XM_PI;
    fog2Re->Pos().y -= 500;
    fog2Re->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    fog2Re->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/newcloud2.png");
    fog2Re->UpdateWorld();


    light = Environment::Get()->GetLight(0);
    light->type = 0;
    light->direction = { -1, -0.3, -1 };
    //    light->color = { 0.57, 0.66, 0.88, 1 }; // 밤조명
    light->color = { 1, 1, 1, 1 };        // 낮조명

    light2 = Environment::Get()->GetLight(1);
    light2->type = 0;
    light2->direction = { -1, -0.3, -1 };
    light2->color = { 0.77, 0.73, 0.65, 1 };        // 낮조명

    light3 = Environment::Get()->GetLight(2);
    light3->type = 0;
    light3->direction = { 1, -0.6, 1 };
    light3->color = { 0.45, 0.45, 0.45, 1 };        // 낮조명

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
    //delete objects;
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
    static bool once = false;
    if (UI->isMapChange == false) // 시작맵
    {
        objects2->Update();
    }
    else // 전투맵
    {
        wireBug->Update();
        if (!once)
        {
            garuk->SetTerrain(terrain);
            player->SetTerrain(terrain);
            CAM->SetTerrain(terrain);
            once = true;
        }
        valphalk->Update();
    }
    player->Update();
    garuk->Update();

    ball->Rot().y += 0.02 * DELTA;
    ball->UpdateWorld();

    ball2->Rot().y += 0.02 * DELTA;
    ball2->UpdateWorld();

    fog->Rot().y -= 0.04 * DELTA;
    fog->UpdateWorld();

    fog2->Rot().y += 0.06 * DELTA;
    fog2->UpdateWorld();

    fogRe->Rot().y -= 0.04 * DELTA;
    fogRe->UpdateWorld();

    fog2Re->Rot().y += 0.06 * DELTA;
    fog2Re->UpdateWorld();

    UIManager::Get()->Update();
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
    valphalk->PreRender();
}

void ShadowScene::Render()
{
    //skyBox->Render();

    //위 함수에서 만들어진 텍스처를 그림자에서 렌더 대상으로 세팅
    if (firstRender == false)
    {
        valphalk->Render();
        firstRender = true;
    }

    //    //그림자를 받기 위한 셰이더 세팅
    //    objects->SetShader(L"Light/Shadow.hlsl");
    //    objects2->SetShader(L"Light/Shadow.hlsl");
    //    valphalk->SetShader(L"Light/Shadow.hlsl");
    //    player->SetShader(L"Light/Shadow.hlsl");
    //    garuk->SetShader(L"Light/Shadow.hlsl");
    //    //셰이더가 세팅된 배경과 인간을 진짜 호출

        //terrain->Render();

    rasterizerState[1]->SetState(); // 후면도 그림
    {
        // val->Render();
        ball->Render();
        ball2->Render();
       
        if (UI->isMapChange == false) // 시작맵
        {
            objects2->Render();
        }
        else // 전투맵
        {
            objects->Render();
//          terrain->Render();
            valphalk->Render();
            objects->Render();
            wireBug->Render();
        }
        blendState[1]->SetState(); // 반투명
        {
            fog->Render();
            fogRe->Render();
            fog2->Render();
            fog2Re->Render();
        }
        blendState[0]->SetState();

        player->Render();
        garuk->Render();
    }
    rasterizerState[0]->SetState();
    if (UI->isMapChange == false)
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
    //    ball->GUIRender();
    //    fog->GUIRender();
    //    cloud->GUIRender();
    //    cloud2->GUIRender();
    //    cloud3->GUIRender();
    //    cloud4->GUIRender();
    //    forest->GUIRender();
    //    terrain->GUIRender();
    //    valphalk->GUIRender();

    player->GUIRender(); // 디버그 조작용
    //    fieldFog->GUIRender();
    //    valphalk->GUIRender();
    //    CAM->GUIRender();
    //    UIManager::Get()->GUIRender();
    //    ItemManager::Get()->GUIRender();
        //player->GUIRender(); // 디버그 조작용
        //UIManager::Get()->GUIRender();
}
