#include "Framework.h"
#include "Wind.h"
Wind::Wind()
{
	particle = new ParticleSystem("TextData/Particles/wind.fx");
	particle2 = new ParticleSystem("TextData/Particles/wind.fx");
	//sprite = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);

	//particle3 = new ParticleSystem("TextData/Particles/potion_05_v2.fx");
	//particle4 = new ParticleSystem("TextData/Particles/potion_04.fx");
	//particle->SetScale();
	//particle2->SetScale();
}

Wind::~Wind()
{
	delete particle;
	delete particle2;
	//delete sprite;
	//delete particle3;
	//delete particle4;
}

void Wind::Update()
{
	particle->ParticleRotate();
	
	//sprite->Update();
	particle->Update();
	particle2->Update();
	//particle3->Update();
	//particle4->Update();
}

void Wind::Render()
{
	//sprite->Render();
	particle->Render();
	particle2->Render();
	//particle3->Render();
	//particle4->Render();
}

void Wind::GUIRender()
{
	particle->GUIRender();
	particle2->GUIRender();

}

void Wind::Play(Vector3 pos, Vector3 rot)
{
	//sprite->Play(pos);
	particle->Play(pos, rot);
	particle2->Play(pos, rot);
	//particle3->Play(pos, rot);
	//particle4->Play(pos, rot);
}

void Wind::PlaySpark(Vector3 pos)
{
	//sprite->Play(pos);
}

void Wind::Stop()
{
	//sprite->Stop();
	particle->Stop();
	particle2->Stop();
	//particle3->Stop();
	//particle4->Stop();
}

void Wind::ParticleRotate()
{
}

void Wind::SetPos(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);
	//particle3->SetPos(pos);
	//particle4->SetPos(pos);
}

void Wind::SetVortex(Vector3 pos)
{
	particle->SetPos(pos);
	particle2->SetPos(pos);

	//particle3->SetPos(pos);
	//particle4->SetPos(pos);
	particle->SetVortex(pos);
	particle2->SetVortex(pos);

}

