#include "Framework.h"
#include "PotionParticle.h"
PotionParticle::PotionParticle()
{
	particle = new ParticleSystem("TextData/Particles/potion_01.fx");
	particle2 = new ParticleSystem("TextData/Particles/potion_02.fx");
	particle3 = new ParticleSystem("TextData/Particles/potion_05_v2.fx");
	particle4 = new ParticleSystem("TextData/Particles/potion_04.fx");
	particle2->SetScale(3.0f);
	//particle3->SetScale();		
}

PotionParticle::~PotionParticle()
{
	delete particle;
	delete particle2;
	delete particle3;
	delete particle4;
}

void PotionParticle::Update()
{
	particle->Update();
	particle2->Update();
	particle3->Update();
	particle4->Update();
}

void PotionParticle::Render()
{
	particle->Render();
	particle2->Render();
	particle3->Render();
	particle4->Render();
}

void PotionParticle::GUIRender()
{
	particle->GUIRender();
	particle2->GUIRender();

}

void PotionParticle::Play(Vector3 pos, Vector3 rot)
{
	particle->Play(pos, rot);
	particle2->Play(pos, rot);
	particle3->Play(pos, rot);
	particle4->Play(pos, rot);
}

void PotionParticle::Stop()
{
	particle->Stop();
	particle2->Stop();
	particle3->Stop();
	particle4->Stop();
}

void PotionParticle::SetPos(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	particle3->SetPos(pos);
	particle4->SetPos(pos);
}

void PotionParticle::SetVortex(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	particle3->SetPos(pos);
	particle4->SetPos(pos);
	
	particle4->SetVortex(pos);
	
}

