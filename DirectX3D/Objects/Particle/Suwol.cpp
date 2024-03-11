#include "Framework.h"
#include "Suwol.h"

Suwol::Suwol()
{
    FOR(30)
    {
        suwol[i] = new Quad(L"Textures/Effect/split/headBreakAtk_2.png");
        suwol[i]->SetParent(this);
        suwol[i]->Scale() *= 6;
        suwol[i]->Pos().y = 100;
        suwol[i]->Pos().x = Random(-100, 100);
        suwol[i]->Pos().z = Random(-100, 100);
        suwol[i]->Rot() = Random({ -1, -0.5, -1 }, { 1, 0.5, 1 });
        suwol[i]->GetMaterial()->SetDiffuseMapColor({ 0.5, 0.5, 1, 1 });
        suwol[i]->UpdateWorld();
    }

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

Suwol::~Suwol()
{
}

void Suwol::Update()
{
    FOR(30)
    {
        suwol[i]->UpdateWorld();
    }
    Transform::UpdateWorld();
}

void Suwol::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();
    rasterizerState[1]->SetState();

    FOR(30)
    {
        suwol[i]->Render();
    }

    blendState[0]->SetState();
    depthState[0]->SetState();
    rasterizerState[0]->SetState();
}

void Suwol::GUIRender()
{
    suwol[0]->GUIRender();
}


