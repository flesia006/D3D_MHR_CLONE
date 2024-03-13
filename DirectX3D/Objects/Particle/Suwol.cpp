#include "Framework.h"
#include "Suwol.h"

Suwol::Suwol()
{
    FOR(count)
    {
        Model* eft = new Model("quad");
        eft->SetParent(this);
        eft->Scale().x *= 0.1;
        eft->Scale().y *= 6;
        eft->Scale().z *= 0.1;
        eft->Pos().y = Random(60, 130);
        eft->Pos().x = Random(-80, 80);
        eft->Pos().z = Random(-80, 80);
        eft->Rot() = Random({ -1, -1.5, -1 }, { 1, 1.5, 1 });
        eft->GetMaterials()[0]->SetDiffuseMap(L"Textures/Effect/split/headBreakAtk_2.png");
        eft->GetMaterials()[0]->SetDiffuseMapColor({ 0.85, 0.95, 0.95, 1 });
        eft->UpdateWorld();
        suwol.push_back(eft);
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

void Suwol::EffectOn()
{
    active = true;
    timer += DELTA;
    if (timer > 0.03 && num < 18)
    {
        for (auto& eft : suwol)
        {
            eft->GetMaterials()[0]->SetDiffuseMapColor({ 0.0f + 0.05f * num, 0.15f + 0.05f * num, 0.15f + 0.05f * num, 1 });
            eft->UpdateWorld();
        }
        num++;
        timer = 0;
    }
}

void Suwol::EffectOff()
{
    timer += DELTA;
    if (timer > 0.03 && num >= 0)
    {
        for (auto& eft : suwol)
        {
            eft->GetMaterials()[0]->SetDiffuseMapColor({ 0.0f + 0.05f * num, 0.15f + 0.05f * num, 0.15f + 0.05f * num, 1 });
            eft->UpdateWorld();
        }
        num--;
        timer = 0;
    }
    if (num == -1)
        active = false;
}

void Suwol::Update()
{
    if (active)
        Transform::UpdateWorld();
}

void Suwol::Render()
{
    if (active)
    {
        blendState[1]->SetState();
        depthState[1]->SetState();
        rasterizerState[1]->SetState();

        for (auto& eft : suwol)
        {
            eft->Render();
        }

        blendState[0]->SetState();
        depthState[0]->SetState();
        rasterizerState[0]->SetState();

    }

}

void Suwol::GUIRender()
{
    suwol[0]->GUIRender();
}


