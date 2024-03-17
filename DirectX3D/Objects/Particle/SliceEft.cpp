#include "Framework.h"
#include "SliceEft.h"

SliceEft::SliceEft()
{
    v_circle = new Cylinder2(400, 100, 32);
    v_circle->SetParent(this);
    v_circle->GetMaterial()->SetDiffuseMap(L"Textures/Effect/bluelight.png");
    v_circle->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    v_circle->UpdateWorld();

    h_circle = new Ring(405, 150, 32);
    h_circle->SetParent(this);
    h_circle->GetMaterial()->SetDiffuseMap(L"Textures/Effect/bluelight.png");
    h_circle->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    h_circle->UpdateWorld();

    v_circle->Rot().y = XM_PI;
    h_circle->Rot().y = XM_PI;
    
    Pos().x += 30;
    Rot().z -= XM_PIDIV4;

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

SliceEft::~SliceEft()
{
}

void SliceEft::Update()
{
    if (!active) return;

    timer += DELTA;
    if (timer < 0.2f)
    {
        v_circle->Rot().y -= 30 * DELTA;
        h_circle->Rot().y -= 30 * DELTA;
    }
    else
    {
        timer = 0.0f;
        v_circle->Rot().y = XM_PI;
        h_circle->Rot().y = XM_PI;
        active = false;
    }


    v_circle->UpdateWorld();
    h_circle->UpdateWorld();
    Transform::UpdateWorld();
}

void SliceEft::Render()
{
    if (active)
    {
        blendState[1]->SetState();
        depthState[1]->SetState();
        rasterizerState[1]->SetState();
        v_circle->Render();
        h_circle->Render();
        blendState[0]->SetState();
        depthState[0]->SetState();
        rasterizerState[0]->SetState();
    }
}
