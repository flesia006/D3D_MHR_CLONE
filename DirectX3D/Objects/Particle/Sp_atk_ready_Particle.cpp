#include "Framework.h"
#include "Sp_atk_ready_Particle.h"
Sp_atk_ready_Particle::Sp_atk_ready_Particle()
{
	sp = new ParticleSystem("TextData/Particles/special_attack_ready_effect.fx");
	halo = new ParticleSystem("TextData/Particles/halo.fx");
	halo->HaloPos();	
}

Sp_atk_ready_Particle::~Sp_atk_ready_Particle()
{
	delete sp;
	delete halo;
}

void Sp_atk_ready_Particle::Update()
{
	sp->Update();
	halo->Update();
}

void Sp_atk_ready_Particle::Render()
{
	sp->Render();
	halo->Render();

}

void Sp_atk_ready_Particle::GUIRender()
{
	sp->GUIRender();
	halo->GUIRender();

}

void Sp_atk_ready_Particle::Play(Vector3 pos, Vector3 rot)
{
	sp->Play(pos, rot);
	halo->Play(pos, rot);
}

void Sp_atk_ready_Particle::Stop()
{
	sp->Stop();
	halo->Stop();
}

