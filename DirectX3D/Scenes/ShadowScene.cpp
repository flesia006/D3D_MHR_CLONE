#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{
    forest = new Model("GroundAll(fix)");
    forest->Pos() += Vector3::Back() * 16000;
    //forest->Scale() *= 0.1f;
    //terrain = new Terrain();
    //terrain->Scale() *= 30;
    //terrain->GlobalScale() *= 30;
    //terrain->GetSize();
    //terrain->UpdateWorld();
    //aStar = new AStar(30, 30);        
    //aStar->SetNode(terrain);

    garuk = new Garuk();
    //garuk->SetTerrain(terrain);
    //garuk->SetAStar(aStar);
    forest = new Model("Forest");
    forest->Scale() *= 10;
    forest->UpdateWorld();

    valphalk = new Valphalk();
    valphalk->Pos().z -= 1500.0f;
    valphalk->Rot().y += XM_PI;
    valphalk->UpdateWorld();

    player = new Player();
    shadow = new Shadow();
    otomo = new ModelAnimator("Otomo");
    otomo->UpdateWorld();
    otomo->ReadClip("O_002", 1);
    otomo->PlayClip(0);
    UIManager::Get();

    // 같이 알아보는 활용법 : 빛 호출 혹은 만들기 (<-빛 사용 방법)    
    light = Environment::Get()->GetLight(0);

    light->type = 0;
    light->pos = { 0, 2000, +1000 };
    light->range = 3000;

    light->direction = { 0, -1, 1 };
    light->color = { 1, 1, 1, 1 };

    light->length;
    light->inner;   //조명 집중 범위 (빛이 집중되어 쏘이는 범위...의 비중)
    light->outer;   //조명 외곽 범위 (빛이 흩어져서 비치는 범위...의 비중)

    skyBox = new SkyBox(L"Textures/Landscape/SpaceSky.dds");
    Sounds::Get()->AddSound("Valphalk_Thema", SoundPath + L"Valphalk_Thema.mp3",true);
    Sounds::Get()->Play("Valphalk_Thema", 0.03f);
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");

    garuk->SetTarget(player);
    //aStar->Update();    
    FOR(2)
        rasterizerSatate[i] = new RasterizerState();
    rasterizerSatate[1]->CullMode(D3D11_CULL_NONE);

}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete player;
    delete shadow;
    delete skyBox;

    //delete terrain;
    //delete aStar;
    delete garuk;

    FOR(2)
        delete rasterizerSatate[i];
}

void ShadowScene::Update()
{
    //if (KEY_DOWN('1')) light->type = 0;
    //if (KEY_DOWN('2')) light->type = 1;
    //if (KEY_DOWN('3')) light->type = 2;
    //if (KEY_DOWN('4')) light->type = 3;


    forest->UpdateWorld();
    valphalk->Update();
    player->Update();
    otomo->Update();
    skyBox->UpdateWorld();
    garuk->Update();
    UIManager::Get()->Update();

    if (player->getCollider()->IsCapsuleCollision(valphalk->GetCollider()[Valphalk::HEAD]))
    {
        UIManager::Get()->Hit(valphalk->damage);
    }
    //aStar->Update();
    //garuk->Control(player);



}

void ShadowScene::PreRender()
{
    //그림자의 렌더 타겟 지정(및 준비)
    shadow->SetRenderTarget();

    //인간한테 뎁스 셰이더를 적용 (조건에 따른 셰이더 변화...등을 가진 조건 함수)
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    player->SetShader(L"Light/DepthMap.hlsl");
    otomo->SetShader(L"Light/DepthMap.hlsl");
    
    garuk->SetShader(L"Light/DepthMap.hlsl");
    //조건에 따라 픽셀이 바뀐 인간을 렌더...해서 텍스처를 준비
    valphalk->Render();
    player->Render();
    otomo->Render();
    garuk->Render();
}

void ShadowScene::Render()
{
    skyBox->Render();

    //위 함수에서 만들어진 텍스처를 그림자에서 렌더 대상으로 세팅
    shadow->SetRender();
    
    //terrain->Render();
    //aStar->Render();    

    //그림자를 받기 위한 셰이더 세팅
    forest->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    otomo->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //셰이더가 세팅된 배경과 인간을 진짜 호출

    rasterizerSatate[1]->SetState();
    forest->Render();
    valphalk->Render();
    otomo->Render();
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
    skyBox->GUIRender();
    //forest->GUIRender();
    //valphalk->GUIRender();
    //player->GUIRender(); // 디버그 조작용
//    UIManager::Get()->GUIRender();
}
