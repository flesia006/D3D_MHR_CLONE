#include "Framework.h"
#include "UseBug.h"

UseBug::UseBug()
{
	FOR(10)usebug.push_back(new ParticleSystem("TextData/Particles/use_bug.fx"));
	bugfinish = new ParticleSystem("TextData/Particles/bugfinish.fx");
	
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	FOR(2) rasterizerState[i] = new RasterizerState();

	FOR(usebug.size())usebug[i]->SetScale(3);
	blendState[1]->Additive();
	//blendState[1]->Alpha(true);

	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
	//depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

	rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

UseBug::~UseBug()
{
}

void UseBug::Update()
{
	FOR(usebug.size())usebug[i]->Update();
	bugfinish->Update();
}

void UseBug::Render()
{
	blendState[1]->SetState();
	depthState[1]->SetState();
	rasterizerState[1]->SetState();
	//bugLightParticle2->Render();
	bugfinish->Render();
	FOR(usebug.size())usebug[i]->Render();
	blendState[0]->SetState();
	depthState[0]->SetState();
	rasterizerState[0]->SetState();
}

void UseBug::GUIRender()
{
}

void UseBug::Play1(Vector3 pos)
{
	usebug[0]->Play(pos);
}

void UseBug::Play2(Vector3 pos)
{
	usebug[1]->Play(pos);
}

void UseBug::Play3(Vector3 pos)
{
	usebug[2]->Play(pos);
}

void UseBug::Play4(Vector3 pos)
{
	usebug[3]->Play(pos);
}

void UseBug::Play5(Vector3 pos)
{
	usebug[4]->Play(pos);
}

void UseBug::Play6(Vector3 pos)
{
	usebug[5]->Play(pos);
}

void UseBug::Play7(Vector3 pos)
{
	usebug[6]->Play(pos);
}

void UseBug::Play8(Vector3 pos)
{
	usebug[7]->Play(pos);
}

void UseBug::Play9(Vector3 pos)
{
	usebug[8]->Play(pos);
}

void UseBug::Play10(Vector3 pos)
{
	bugfinish->Play(pos);
}

void UseBug::Stop()
{
}

void UseBug::SetPos(Vector3 pos)
{
}
