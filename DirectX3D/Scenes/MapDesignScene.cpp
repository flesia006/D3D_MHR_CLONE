#include "Framework.h"
#include "MapDesignScene.h"

MapDesignScene::MapDesignScene()
{
    objects = new M41Objects();

    val = new DummyValphalk();
    val->Pos() = Vector3(3000, 153.3, 3000);
    val->Rot().y += XM_PI;

    cap = new CapsuleCollider(5, 6000);
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

    fieldFog = new Model("fog");
    fieldFog->Pos() = Vector3(2062.1f, 230, 17653.896f);
    fieldFog->Rot().y = XM_PI;
    fieldFog->UpdateWorld();


    light = Environment::Get()->GetLight(0);
    light->type = 0;
    light->direction = { -1, -0.3, -1 };
    //    light->color = { 0.57, 0.66, 0.88, 1 }; // ¹ãÁ¶¸í
    light->color = { 1, 1, 1, 1 };        // ³·Á¶¸í

    light2 = Environment::Get()->GetLight(1);
    light2->type = 0;
    light2->direction = { -1, -0.3, -1 };
    light2->color = { 0.77, 0.73, 0.65, 1 };        // ³·Á¶¸í

    light2 = Environment::Get()->GetLight(2);
    light2->type = 0;
    light2->direction = { 1, -0.6, 1 };
    light2->color = { 0.45, 0.45, 0.45, 1 };        // ³·Á¶¸í


    FOR(2) rasterizerState[i] = new RasterizerState();
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Additive();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

MapDesignScene::~MapDesignScene()
{

}

void MapDesignScene::Update()
{
    objects->Update();
    ball->Rot().y += 0.02 * DELTA;
    ball->UpdateWorld();

    ball2->Rot().y += 0.02 * DELTA;
    ball2->UpdateWorld();

    if (KEY_DP('W')) cap->Pos().x += 5;
    if (KEY_DP('S')) cap->Pos().x -= 5;
    if (KEY_DP('A')) cap->Pos().z += 5;
    if (KEY_DP('D')) cap->Pos().z -= 5;

    cap->Update();
    fog->Rot().y -= 0.04 * DELTA;
    fog->UpdateWorld();

    fog2->Rot().y += 0.06 * DELTA;
    fog2->UpdateWorld();

    val->Update();

}

void MapDesignScene::PreRender()
{
}

void MapDesignScene::Render()
{

    rasterizerState[1]->SetState(); // ÈÄ¸éµµ ±×¸²
    {
        objects->Render();
        val->Render();
        ball->Render();
        ball2->Render();
        blendState[1]->SetState(); // ¹ÝÅõ¸í
        {
            fog->Render();
            fog2->Render();
            //fieldFog->Render();
        }
        blendState[0]->SetState();
    }
    rasterizerState[0]->SetState();

    cap->Render();
}

void MapDesignScene::PostRender()
{
}

void MapDesignScene::GUIRender()
{
    objects->GUIRender(); 
    //ball2->GUIRender();
//    val->GUIRender();
//      ball->GUIRender();
//    fog->GUIRender();
//    
    cap->GUIRender();
}
