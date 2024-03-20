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

    wireBug->Pos() = { 313,215.9f,4282 };

    shadow = new Shadow();
    UIManager::Get();

    // ���� �˾ƺ��� Ȱ��� : �� ȣ�� Ȥ�� ����� (<-�� ��� ���)    
    light = Environment::Get()->GetLight(0);

    light->type = 0;
    light->pos = { 0, 3000, +3000 };
    light->range = 3000;

    light->direction = { -0.1, -1, 0.1 };
//    light->color = { 0.57, 0.66, 0.88, 1 }; // ������
    light->color = { 1, 1, 1, 1 };        // ������

    light->length;
    light->inner;   //���� ���� ���� (���� ���ߵǾ� ���̴� ����...�� ����)
    light->outer;   //���� �ܰ� ���� (���� ������� ��ġ�� ����...�� ����)


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
    if (UI->isMapChange == false) // ���۸�
    {
        player->Pos().y = 10;
        garuk->Pos().y = 10;
        objects2->Update();
        wireBug->Update();
    }
    else // ������
    {
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
    //�׸����� ���� Ÿ�� ����(�� �غ�)
    //shadow->SetRenderTarget();

    ////�ΰ����� ���� ���̴��� ���� (���ǿ� ���� ���̴� ��ȭ...���� ���� ���� �Լ�)
    //objects->SetShader(L"Light/DepthMap.hlsl");
    //valphalk->SetShader(L"Light/DepthMap.hlsl");
    //player->SetShader(L"Light/DepthMap.hlsl");
    //garuk->SetShader(L"Light/DepthMap.hlsl");
    ////���ǿ� ���� �ȼ��� �ٲ� �ΰ��� ����...�ؼ� �ؽ�ó�� �غ�
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

    //�� �Լ����� ������� �ؽ�ó�� �׸��ڿ��� ���� ������� ����
    shadow->SetRender();
    if (firstRender == false)
    {
        valphalk->Render();
        objects->Render();
        firstRender = true;
    }

    //�׸��ڸ� �ޱ� ���� ���̴� ����
    objects->SetShader(L"Light/Shadow.hlsl");
    objects2->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //���̴��� ���õ� ���� �ΰ��� ��¥ ȣ��

    //terrain->Render();

    rasterizerState[1]->SetState(); // �ĸ鵵 �׸�
    {
        ball->Render();        
        if (UI->isMapChange == false) // ���۸�
        {
            objects2->Render();
            wireBug->Render();
        }
        else // ������
        {
            valphalk->Render();
            objects->Render();
        }
    }
    rasterizerState[0]->SetState();
    
    player->Render();
    garuk->Render();

    rasterizerState[1]->SetState();
    blendState[1]->SetState(); // ������
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
    //shadow->PostRender(); // ���� ��¿�
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
      
    player->GUIRender(); // ����� ���ۿ�
    fieldFog->GUIRender();
    valphalk->GUIRender();
    CAM->GUIRender();
    UIManager::Get()->GUIRender();
    ItemManager::Get()->GUIRender();
    //player->GUIRender(); // ����� ���ۿ�
    //UIManager::Get()->GUIRender();
}
