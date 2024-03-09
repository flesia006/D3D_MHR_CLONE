#include "Framework.h"
#include "Sp_atk_start.h"
Sp_atk_start::Sp_atk_start()
{
	sp = new ParticleSystem("TextData/Particles/sp_start_01.fx");
	sp1 = new ParticleSystem("TextData/Particles/sp_start_02.fx");
	sp->SetScale(2);
	sp1->SetScale(2);

}

Sp_atk_start::~Sp_atk_start()
{
	delete sp;
	delete sp1;
}

void Sp_atk_start::Update()
{
	sp->Update();
	sp1->Update();
}

void Sp_atk_start::Render()
{
	sp1->Render();
	sp->Render();

}

void Sp_atk_start::GUIRender()
{
	sp->GUIRender();
	sp1->GUIRender();

}

void Sp_atk_start::Play(Vector3 pos, Vector3 rot)
{
	sp->Play(pos, rot);
	sp1->Play(pos, rot);
}

void Sp_atk_start::Stop()
{
	sp->Stop();
	sp1->Stop();
}

