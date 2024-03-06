#include "Framework.h"
#include "Val_Jet_Particle.h"

Val_Jet_Particle::Val_Jet_Particle()
{
	jet = new ParticleSystem("TextData/Particles/val_jet_v2.fx");	
	jet->SetScale();
}

Val_Jet_Particle::~Val_Jet_Particle()
{
	delete jet;
}

void Val_Jet_Particle::Update()
{	
	jet->Update();
}

void Val_Jet_Particle::Render()
{
	jet->Render();
}

void Val_Jet_Particle::GUIRender()
{
	jet->GUIRender();
}

void Val_Jet_Particle::Play(Vector3 pos, Vector3 rot)
{
	//jet->SetRotation(rot);
	jet->Play(pos, rot);
}

void Val_Jet_Particle::Stop()
{
	jet->Stop();
}

void Val_Jet_Particle::SetPos(Vector3 pos)
{
	jet->SetPos(pos);	
}

