#include "Framework.h"
#include "Sp_atk_success.h"
Sp_atk_success::Sp_atk_success()
{
	sp = new ParticleSystem("TextData/Particles/sp_start_01.fx");
	sp1 = new ParticleSystem("TextData/Particles/sp_success_01.fx");
	sp->SetScale(2);
	sp1->SetScale(2);
	
}

Sp_atk_success::~Sp_atk_success()
{
	delete sp;
	delete sp1;
}

void Sp_atk_success::Update()
{
	sp->Update();
	sp1->Update();

}

void Sp_atk_success::Render()
{
	sp1->Render();
	sp->Render();

}

void Sp_atk_success::GUIRender()
{
	sp->GUIRender();
	sp1->GUIRender();

}

void Sp_atk_success::Play(Vector3 pos, Vector3 rot)
{
	sp->Play(pos, rot);
	sp1->Play(pos, rot);
}

void Sp_atk_success::Stop()
{
	sp->Stop();
	sp1->Stop();
}

void Sp_atk_success::SetPos(Vector3 pos)
{
	sp->SetPos(pos);
	sp1->SetPos(pos);
}

