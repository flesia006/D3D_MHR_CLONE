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

    // ���� �˾ƺ��� Ȱ��� : �� ȣ�� Ȥ�� ����� (<-�� ��� ���)    
    light = Environment::Get()->GetLight(0);

    light->type = 0;
    light->pos = { 0, 2000, +1000 };
    light->range = 3000;

    light->direction = { 0, -1, 1 };
    light->color = { 1, 1, 1, 1 };

    light->length;
    light->inner;   //���� ���� ���� (���� ���ߵǾ� ���̴� ����...�� ����)
    light->outer;   //���� �ܰ� ���� (���� ������� ��ġ�� ����...�� ����)

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
    //�׸����� ���� Ÿ�� ����(�� �غ�)
    shadow->SetRenderTarget();

    //�ΰ����� ���� ���̴��� ���� (���ǿ� ���� ���̴� ��ȭ...���� ���� ���� �Լ�)
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    player->SetShader(L"Light/DepthMap.hlsl");
    otomo->SetShader(L"Light/DepthMap.hlsl");
    
    garuk->SetShader(L"Light/DepthMap.hlsl");
    //���ǿ� ���� �ȼ��� �ٲ� �ΰ��� ����...�ؼ� �ؽ�ó�� �غ�
    valphalk->Render();
    player->Render();
    otomo->Render();
    garuk->Render();
}

void ShadowScene::Render()
{
    skyBox->Render();

    //�� �Լ����� ������� �ؽ�ó�� �׸��ڿ��� ���� ������� ����
    shadow->SetRender();
    
    //terrain->Render();
    //aStar->Render();    

    //�׸��ڸ� �ޱ� ���� ���̴� ����
    forest->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    otomo->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //���̴��� ���õ� ���� �ΰ��� ��¥ ȣ��

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
    //shadow->PostRender(); // ���� ��¿�
    player->PostRender();
    UIManager::Get()->PostRender();
}

void ShadowScene::GUIRender()
{
    skyBox->GUIRender();
    //forest->GUIRender();
    //valphalk->GUIRender();
    //player->GUIRender(); // ����� ���ۿ�
//    UIManager::Get()->GUIRender();
}
