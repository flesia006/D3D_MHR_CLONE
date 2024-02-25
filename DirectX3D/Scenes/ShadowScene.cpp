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
    //�׸����� ���� Ÿ�� ����(�� �غ�)
    shadow->SetRenderTarget();

    //�ΰ����� ���� ���̴��� ���� (���ǿ� ���� ���̴� ��ȭ...���� ���� ���� �Լ�)
    objects->SetShader(L"Light/DepthMap.hlsl");
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    player->SetShader(L"Light/DepthMap.hlsl");
    garuk->SetShader(L"Light/DepthMap.hlsl");
    //���ǿ� ���� �ȼ��� �ٲ� �ΰ��� ����...�ؼ� �ؽ�ó�� �غ�
    objects->Render();
    valphalk->Render();
    player->Render();
    
    garuk->Render();
}

void ShadowScene::Render()
{
    //skyBox->Render();

    //�� �Լ����� ������� �ؽ�ó�� �׸��ڿ��� ���� ������� ����
    shadow->SetRender();


    //�׸��ڸ� �ޱ� ���� ���̴� ����
    objects->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    garuk->SetShader(L"Light/Shadow.hlsl");
    //���̴��� ���õ� ���� �ΰ��� ��¥ ȣ��

    //terrain->Render();

    rasterizerState[1]->SetState(); // �ĸ鵵 �׸�
    {
        ball->Render();        
        valphalk->Render();
        objects->Render();
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

}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // ���� ��¿�
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
//    player->GUIRender(); // ����� ���ۿ�
    fieldFog->GUIRender();
    valphalk->GUIRender();
    //player->GUIRender(); // ����� ���ۿ�
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
    // ��ȿ
    sound->AddSound("em086_05_vo_media_10", SoundPath + L"em086_05_vo_media_10.mp3");
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

    /////////////////////////////////////////////////////////////
    // Item
    Sounds::Get()->AddSound("health_potion", SoundPath + L"health_potion.mp3");
}
