#include "Framework.h"
#include "HitParticle.h"

HitParticle::HitParticle()
{
	hit1 = new ParticleSystem("TextData/Particles/Hit1_fix2.fx");
	hit2 = new ParticleSystem("TextData/Particles/Hit2_fix2.fx");


}

HitParticle::~HitParticle()
{
	delete hit1;
	delete hit2;
}

void HitParticle::Update()
{
	hit1->Update();
	hit2->Update();
}

void HitParticle::Render()
{
	hit1->Render();
	hit2->Render();

}

void HitParticle::GUIRender()
{
	hit1->GUIRender();	
	hit2->GUIRender();
	
}

void HitParticle::Play(Vector3 pos, Vector3 rot)
{
	hit1->Play(pos, rot);
	hit2->Play2(pos, rot);
}

void HitParticle::Stop()
{
	hit1->Stop();
	hit2->Stop();
}

