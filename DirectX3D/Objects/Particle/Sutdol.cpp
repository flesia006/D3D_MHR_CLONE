#include "Framework.h"
#include "Sutdol.h"

Sutdol::Sutdol()
{
	spark = new ParticleSystem("TextData/Particles/sutdol_effect.fx");
	halo = new ParticleSystem("TextData/Particles/sutdol_halo.fx");
}

Sutdol::~Sutdol()
{
	delete spark;
	delete halo;
}

void Sutdol::Update()
{
	spark->Update();
	halo->Update();
	
	
}

void Sutdol::Render()
{
	spark->Render();
	halo->Render();
}

void Sutdol::GUIRender()
{
	spark->GUIRender();
}

void Sutdol::Play(Vector3 pos, Vector3 rot)
{
	spark->Play(pos, rot);
}

void Sutdol::PlayHalo(Vector3 pos)
{
	halo->Play(pos);
}

void Sutdol::Stop()
{
	spark->Stop();
}

void Sutdol::ParticleRotate()
{
	spark->ParticleRotate();
}

void Sutdol::SetPos(Vector3 pos)
{
	spark->SetPos(pos);
	halo->SetPos(pos);
}

