#include "Framework.h"
#include "FullBurstParticle.h"

FullBurstParticle::FullBurstParticle()
{
    zet1 = new Quad(L"Textures/Effect/valzet/val1.png");
    zet2 = new Quad(L"Textures/Effect/valzet/val1.png");
    zet1->Scale() *= 42;
    zet1->Scale().y *= 2.5;
    //zet1->Pos().y += 650;
    zet1->SetParent(this);
    zet1->UpdateWorld();

    zet2->Scale() *= 45;
    zet2->Scale().y *= 2.5;
    //zet2->Pos().y += 650;
    zet2->Rot().y += XM_PIDIV2;
    zet2->SetParent(this);
    zet2->UpdateWorld();
    zet1->Pos().y += 200;
    zet2->Pos().y += 200;

    zet1->Rot().x -= XM_PIDIV2;
    zet2->Rot().z -= XM_PIDIV2;


    particle = new ParticleSystem("TextData/Particles/val_energy.fx");
    particle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
    sprite = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);
    particle->SetScale(6.0f);
    particle2->SetScale(6.0f);

    //zet1->Pos().z -= 1000;
    //zet2->Pos().z -= 1000;
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    //blendState[1]->Alpha(true);
    blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
	

    //FOR(10)beamSpark[i]->SetPos({ Pos().x,Pos().y,Pos().z - 1000 });

    zet1Scale = zet1->Scale();
    zet2Scale = zet2->Scale();
}

FullBurstParticle::~FullBurstParticle()
{
	delete zet1;
	delete zet2;
}

void FullBurstParticle::Update()
{
    timer += DELTA;    
    sprite->Update();
    particle->Update();
    particle2->Update();
    
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

    //zet1->Rot().y += 500 * DELTA;
    zet2->Rot().x += 5000 * DELTA;

    zet1->UpdateWorld();
    zet2->UpdateWorld();

    Transform::UpdateWorld();

}

void FullBurstParticle::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();
    rasterizerState[1]->SetState();

    zet1->Render();
    zet2->Render();
    //sprite->Render();
    //particle->Render();
    //particle2->Render();

    blendState[0]->SetState();
    depthState[0]->SetState();
    rasterizerState[0]->SetState();
}

void FullBurstParticle::GUIRender()
{
    //ImGui::SliderFloat3("zet1", (float*)&zet1->Rot(), -3.14, 3.14);
    zet1->GUIRender();
}

void FullBurstParticle::Play(Vector3 pos, Vector3 rot)
{   
    particle->Play(pos);
    particle2->Play(pos);
}

void FullBurstParticle::PlaySpark(Vector3 pos, Vector3 rot, int num)
{
}

void FullBurstParticle::Stop()
{
}

void FullBurstParticle::ParticleRotate()
{
}

void FullBurstParticle::PlayAlpha()
{
    zet1->Scale().x = Lerp(zet1->Scale().x, 0, 0.02f);
    zet2->Scale().x = Lerp(zet2->Scale().x, 0, 0.02f);
}

void FullBurstParticle::RepairZet()
{
    zet1->Scale() = zet1Scale;
    zet2->Scale() = zet2Scale;
}

