#include "Framework.h"
#include "Val_fire.h"
Val_fire::Val_fire()
{
	particle = new ParticleSystem("TextData/Particles/val_energy.fx");
	particle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
	sprite = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);

	//particle3 = new ParticleSystem("TextData/Particles/potion_05_v2.fx");
	//particle4 = new ParticleSystem("TextData/Particles/potion_04.fx");
	//particle2->SetScale();
	//particle3->SetScale();		
	particle->SetScale();
	particle2->SetScale();	
}

Val_fire::~Val_fire()
{
	delete particle;
	delete particle2;
	delete sprite;
	//delete particle3;
	//delete particle4;
}

void Val_fire::Update()
{
	sprite->Update();
	particle->Update();
	particle2->Update();
	//particle3->Update();
	//particle4->Update();
}

void Val_fire::Render()
{
	sprite->Render();
	particle->Render();
	particle2->Render();
	//particle3->Render();
	//particle4->Render();
}

void Val_fire::GUIRender()
{
	particle->GUIRender();
	particle2->GUIRender();

}

void Val_fire::Play(Vector3 pos, Vector3 rot)
{
	//sprite->Play(pos);
	particle->Play(pos, rot);
	particle2->Play(pos, rot);
	//particle3->Play(pos, rot);
	//particle4->Play(pos, rot);
}

void Val_fire::PlaySpark(Vector3 pos)
{
	sprite->Play(pos);
}

void Val_fire::Stop()
{
	sprite->Stop();
	particle->Stop();
	particle2->Stop();
	//particle3->Stop();
	//particle4->Stop();
}

void Val_fire::ParticleRotate()
{
}

void Val_fire::SetPos(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	//particle3->SetPos(pos);
	//particle4->SetPos(pos);
}

void Val_fire::SetVortex(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	
	//particle3->SetPos(pos);
	//particle4->SetPos(pos);

	particle2->SetVortex(pos);

}

