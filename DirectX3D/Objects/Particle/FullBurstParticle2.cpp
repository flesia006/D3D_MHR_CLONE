#include "Framework.h"
#include "FullBurstParticle2.h"

FullBurstParticle2::FullBurstParticle2()
{   
    particle = new ParticleSystem("TextData/Particles/val_energy.fx");
    particle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
    sprite = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    sprite2 = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    sprite3 = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    sprite4 = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    sprite5 = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    sprite6 = new Sprite(L"Textures/Effect/val_spark.png", 2650, 2650, 8, 4, true);
    particle->SetScale(13.0f);
    particle2->SetScale(13.0f);

    //zet1->Pos().z -= 1000;
    //zet2->Pos().z -= 1000;
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    FOR(2) rasterizerState[i] = new RasterizerState();

    blendState[1]->Alpha(false);
    //blendState[1]->Additive();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

FullBurstParticle2::~FullBurstParticle2()
{
}

void FullBurstParticle2::Update()
{
    sprite->Update();
    sprite2->Update();
    sprite3->Update();
    sprite4->Update();
    sprite5->Update();
    sprite6->Update();
    particle->Update();
    particle2->Update();  

}

void FullBurstParticle2::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();
    rasterizerState[1]->SetState();    
    
    sprite->Render();
    sprite2->Render();
    sprite3->Render();
    sprite4->Render();
    sprite5->Render();
    sprite6->Render();
    particle->Render();
    particle2->Render();

    blendState[0]->SetState();
    depthState[0]->SetState();
    rasterizerState[0]->SetState();
}

void FullBurstParticle2::GUIRender()
{
}

void FullBurstParticle2::Play(Vector3 pos, Vector3 rot)
{
    particle->Play(pos);
    particle2->Play(pos);
}

void FullBurstParticle2::PlaySpark(Vector3 pos, Vector3 rot)
{
    sprite->Play(pos);
}

void FullBurstParticle2::SetPos(Vector3 pos)
{
    particle->SetPos(pos);
    particle2->SetPos(pos);
}

void FullBurstParticle2::Stop()
{
    particle->Stop();
    particle2->Stop();
}

void FullBurstParticle2::ParticleRotate()
{
}

