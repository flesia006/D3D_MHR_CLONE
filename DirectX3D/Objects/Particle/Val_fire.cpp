#include "Framework.h"
#include "Val_fire.h"
Val_fire::Val_fire()
{
	explosionParticle = new ParticleSystem("TextData/Particles/explosion_Particle.fx");
	
	particle = new ParticleSystem("TextData/Particles/val_energy.fx");
	particle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
	sprite = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);	

	bulletExplosion1 = new Sprite(L"Textures/Effect/Smoke.png", 550, 550, 8, 6, false);
	bulletExplosion2 = new Sprite(L"Textures/Effect/Boom.png", 750, 750, 5, 4, false);
	bulletExplosion3 = new Sprite(L"Textures/Effect/Boom.png", 750, 750, 5, 4, false);
	bulletExplosion4 = new Sprite(L"Textures/Effect/Boom.png", 750, 750, 5, 4, false);
	bulletSparkExplosion = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);
	particle->SetScale(3.0f);
	particle2->SetScale(3.0f);	

	burstparticle1 = new ParticleSystem("TextData/Particles/val_energy.fx");
	burstparticle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
	burstparticle1->SetScale(4.f);
	burstparticle2->SetScale(4.f);

}

Val_fire::~Val_fire()
{
	delete explosionParticle;
	delete particle;
	delete particle2;
	delete burstparticle1;
	delete burstparticle2;
	delete sprite;
	delete bulletExplosion1;
	delete bulletExplosion2;
	delete bulletExplosion3;
	delete bulletExplosion4;
	delete bulletSparkExplosion;
}

void Val_fire::Update()
{
	explosionParticle->Update();
	sprite->Update();
	particle->Update();
	particle2->Update();
	burstparticle1->Update();
	burstparticle2->Update();
	bulletExplosion1->Update();
	bulletExplosion2->Update();
	bulletExplosion3->Update();
	bulletExplosion4->Update();
	bulletSparkExplosion->Update();
	//if (particle->GetPos().y <= 1 && IsActive() == true)
	//{
	//	bulletExplosion1->Play(particle->GetPos());
	//	bulletExplosion2->Play(particle->GetPos());
	//	bulletExplosion3->Play(particle->GetPos());
	//	bulletExplosion4->Play(particle->GetPos());
	//}	
}

void Val_fire::Render()
{
	explosionParticle->Render();
	bulletSparkExplosion->Render();
	bulletExplosion1->Render();
	bulletExplosion2->Render();
	bulletExplosion3->Render();
	bulletExplosion4->Render();
	sprite->Render();
	particle->Render();
	particle2->Render();
	burstparticle1->Render();
	burstparticle2->Render();
}

void Val_fire::GUIRender()
{
	particle->GUIRender();
	particle2->GUIRender();

}

void Val_fire::Play(Vector3 pos, Vector3 rot)
{
	particle->Play(pos, rot);
	particle2->Play(pos, rot);
}

void Val_fire::PlaySpark(Vector3 pos)
{
	sprite->Play(pos);
}

void Val_fire::Stop()
{
	//bulletSparkExplosion->Stop();
	//explosionParticle->Stop();
	sprite->Stop();
	particle->Stop();
	particle2->Stop();
	burstparticle1->Stop();
	burstparticle2->Stop();
}

void Val_fire::ParticleRotate()
{
}

void Val_fire::SetPos(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);

	burstparticle1->SetPos(pos);
	burstparticle2->SetPos(pos);
}

void Val_fire::SetVortex(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	

	particle2->SetVortex(pos);

}

void Val_fire::PlayExplosion()
{
	explosionParticle->Play(particle->GetPos());
	bulletExplosion1->Play(particle->GetPos());
	bulletExplosion2->Play(particle->GetPos());
	bulletExplosion3->Play(particle->GetPos());
	bulletExplosion4->Play(particle->GetPos());
}

void Val_fire::PlaySpark()
{
	bulletSparkExplosion->Play(particle->GetPos());
}

void Val_fire::FullBurstScale(Vector3 pos)
{
	burstparticle1->Play(pos);
	burstparticle2->Play(pos);

}

