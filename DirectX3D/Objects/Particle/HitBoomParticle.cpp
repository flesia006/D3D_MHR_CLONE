#include "Framework.h"
#include "HitBoomParticle.h"

HitBoomParticle::HitBoomParticle()
{
	hit = new ParticleSystem("TextData/Particles/hhit.fx");		
}

HitBoomParticle::~HitBoomParticle()
{
	delete hit;	
}

void HitBoomParticle::Update()
{
	hit->Update();	
}

void HitBoomParticle::Render()
{
	hit->Render();
}

void HitBoomParticle::GUIRender()
{
	hit->GUIRender();
}

void HitBoomParticle::Play(Vector3 pos, Vector3 rot)
{
	hit->Play(pos, rot);	
}

void HitBoomParticle::Stop()
{
	hit->Stop();	
}

