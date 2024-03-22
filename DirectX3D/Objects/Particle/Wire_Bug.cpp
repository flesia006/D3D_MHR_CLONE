#include "Framework.h"
#include "Wire_Bug.h"
Wire_Bug::Wire_Bug()
{
	particle = new ParticleSystem("TextData/Particles/wire_bug.fx");
	//particle2 = new ParticleSystem("TextData/Particles/val_energy2.fx");
	//sprite = new Sprite(L"Textures/Effect/val_spark.png", 750, 750, 8, 4, true);
	particle->SetRot({ 0,0,XM_PIDIV2 });
	//particle3 = new ParticleSystem("TextData/Particles/potion_05_v2.fx");
	//particle4 = new ParticleSystem("TextData/Particles/potion_04.fx");
	//particle2->SetScale();
	//particle3->SetScale();		
	//particle->SetScale();
	//particle2->SetScale(3.0f);
}

Wire_Bug::~Wire_Bug()
{
	delete particle;
	//delete particle2;
	//delete sprite;
	//delete particle3;
	//delete particle4;
}

void Wire_Bug::Update()
{
	//sprite->Update();
	particle->Update();
	//particle2->Update();
	//particle3->Update();
	//particle4->Update();
}

void Wire_Bug::Render()
{
	//sprite->Render();
	particle->Render();
	//particle2->Render();
	//particle3->Render();
	//particle4->Render();
}

void Wire_Bug::GUIRender()
{
	//particle->GUIRender();
	//particle2->GUIRender();
}

void Wire_Bug::Play(Vector3 pos, Vector3 rot)
{
	//sprite->Play(pos);
	particle->Play(pos, rot);
	//particle2->Play(pos, rot);
	//particle3->Play(pos, rot);
	//particle4->Play(pos, rot);
}

void Wire_Bug::PlaySpark(Vector3 pos)
{
	//sprite->Play(pos);
}

void Wire_Bug::Stop()
{
	//sprite->Stop();
	particle->Stop();
	//particle2->Stop();
	//particle3->Stop();
	//particle4->Stop();
}

void Wire_Bug::ParticleRotate()
{
}

void Wire_Bug::SetPos(Vector3 pos)
{
	particle->SetPos(pos);
	//particle2->SetPos(pos);
	//particle3->SetPos(pos);
	//particle4->SetPos(pos);
}

void Wire_Bug::SetVortex(Vector3 pos)
{
	particle->SetPos(pos);
	//particle2->SetPos(pos);

	//particle3->SetPos(pos);
	//particle4->SetPos(pos);

	//particle2->SetVortex(pos);

}

