#include "Framework.h"
#include "CriticalParticle.h"

CriticalParticle::CriticalParticle()
{
	hit = new ParticleSystem("TextData/Particles/Critical_fix.fx");	
}

CriticalParticle::~CriticalParticle()
{
	delete hit;
}

void CriticalParticle::Update()
{
	hit->Update();
}

void CriticalParticle::Render()
{
	hit->Render();
}

void CriticalParticle::GUIRender()
{
	hit->GUIRender();
}

void CriticalParticle::Play(Vector3 pos, Vector3 rot)
{
	hit->Play(pos, rot);
}

void CriticalParticle::Stop()
{
	hit->Stop();
}

void CriticalParticle::ParticleRotate()
{
	hit->ParticleRotate();
}

