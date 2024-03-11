#include "Framework.h"
#include "TuguEft.h"


TuguEft::TuguEft()
{
    tugu = new Quad(L"Textures/Effect/split/headBreakAtk_1.png");
    tugu->Scale() *= 5;
    tugu->Pos().y += 300;
    tugu->SetParent(this);
    tugu->UpdateWorld();

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

TuguEft::~TuguEft()
{

}

void TuguEft::Update()
{
    if (!active)
        return;
    timer += DELTA;

    if (timer >= 0.04f)
    {
        wstring path = L"Textures/Effect/split/headBreakAtk_" + to_wstring(num) + L".png";
        tugu->GetMaterial()->SetDiffuseMap(path);

        Rot().x = CAM->Rot().x;
        Rot().y = CAM->Rot().y;

        timer = 0.0f;
        num++;
        if (num > 4)
        {
            num = 1;
            active = false;
        }
    }


    tugu->UpdateWorld();
    Transform::UpdateWorld();
}

void TuguEft::Render()
{
    if (active)
    {
        blendState[1]->SetState();
        depthState[1]->SetState();
        rasterizerState[1]->SetState();
        tugu->Render();
        blendState[0]->SetState();
        depthState[0]->SetState();
        rasterizerState[0]->SetState();
    }

}
