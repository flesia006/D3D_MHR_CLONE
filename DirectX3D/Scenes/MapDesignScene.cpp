#include "Framework.h"
#include "MapDesignScene.h"

MapDesignScene::MapDesignScene()
{
    objects = new M41Objects();

    cap = new CapsuleCollider(5, 6000);
    ball = new HalfSphere();
    ball->Scale() *= 150000;
    ball->Pos().y -= 6000;
    ball->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    ball->GetMaterial()->SetDiffuseMap(L"Textures/M41Sky/Sky.tga");
    ball->UpdateWorld();

    fog = new Model("skydom");
    fog->SetTag("fog");
    fog->Scale() *= 100;
    fog->Pos().y -= 10000;
    fog->UpdateWorld();

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

    if (KEY_DP('W')) cap->Pos().x += 5;
    if (KEY_DP('S')) cap->Pos().x -= 5;
    if (KEY_DP('A')) cap->Pos().z += 5;
    if (KEY_DP('D')) cap->Pos().z -= 5;

    cap->Update();
    fog->Rot().y += 0.04 * DELTA;
    fog->UpdateWorld();
}

void MapDesignScene::PreRender()
{
}

void MapDesignScene::Render()
{

    rasterizerState[1]->SetState(); // 후면도 그림
    {
        objects->Render();
        ball->Render();

        blendState[1]->SetState(); // 반투명
        {
            fog->Render();
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
    //objects->GUIRender(); 
//      ball->GUIRender();
//    fog->GUIRender();
//    
    cap->GUIRender();
}
