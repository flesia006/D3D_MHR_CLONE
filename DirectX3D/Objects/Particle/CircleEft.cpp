#include "Framework.h"
#include "CircleEft.h"

CircleEft::CircleEft()
{
    v_circle = new Cylinder2(400, 100, 32);
    v_circle->Rot().y += 1.308f;
    v_circle->SetParent(this);
    v_circle->GetMaterial()->SetDiffuseMap(L"Textures/Effect/split/Atk_1");
    v_circle->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    v_circle->UpdateWorld();

    h_circle = new Ring(405, 150, 32);
    h_circle->Rot().y += 1.308f;
    h_circle->SetParent(this);
    h_circle->GetMaterial()->SetDiffuseMap(L"Textures/Effect/split/Atk_1");
    h_circle->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    h_circle->UpdateWorld();

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

CircleEft::~CircleEft()
{
}

void CircleEft::Update()
{
    if (!active)
        return;
    timer += DELTA;

    if (timer >= 0.04f)
    {
        wstring path = L"Textures/Effect/split/Atk_" + to_wstring(num) + L".png";
        v_circle->GetMaterial()->SetDiffuseMap(path);
        h_circle->GetMaterial()->SetDiffuseMap(path);

        timer = 0.0f;
        num++;
        if (num > 4)
        {
            num = 1;
        }
    }
    v_circle->Rot().y += 50 * DELTA;
    h_circle->Rot().y += 50 * DELTA;
    v_circle->UpdateWorld();
    h_circle->UpdateWorld();
    Transform::UpdateWorld();
}

void CircleEft::Render()
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
