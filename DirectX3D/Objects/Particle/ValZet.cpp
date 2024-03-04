#include "Framework.h"
#include "ValZet.h"

ValZet::ValZet()
{
    zet1 = new Quad(L"Textures/Effect/valzet/val1.png");
    zet2 = new Quad(L"Textures/Effect/valzet/val1.png");
    zet1->Scale() *= 4;
    zet1->Scale().y *= 2.5;
    zet1->Pos().y += 650;
    zet1->SetParent(this);
    zet1->UpdateWorld();

    zet2->Scale() *= 4;
    zet2->Scale().y *= 2.5;
    zet2->Pos().y += 650;
    zet2->Rot().y += XM_PIDIV2;
    zet2->SetParent(this);
    zet2->UpdateWorld();

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

ValZet::~ValZet()
{
}

void ValZet::Update()
{
    timer += DELTA;

    if (timer >= 0.01f)
    {
        wstring path = L"Textures/Effect/valzet/val" + to_wstring(num) + L".png";
        zet1->GetMaterial()->SetDiffuseMap(path);
        zet2->GetMaterial()->SetDiffuseMap(path);

        timer = 0.0f;
        num++;
        if (num > 4)
            num = 1;
    }

    zet1->Rot().y += 500 * DELTA;
    zet2->Rot().y += 500 * DELTA;

    zet1->UpdateWorld();
    zet2->UpdateWorld();
    Transform::UpdateWorld();
}

void ValZet::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();
    rasterizerState[1]->SetState();
    zet1->Render();
    zet2->Render();
    blendState[0]->SetState();
    depthState[0]->SetState();
    rasterizerState[0]->SetState();
}
