#include "Framework.h"
#include "HupgiFire.h"
HupgiFire::HupgiFire()
{
	sprite = new Sprite(L"Textures/Effect/hupgifire001.png", 500, 500, 4, 8, false);

	//particle3 = new ParticleSystem("TextData/Particles/potion_05_v2.fx");
	//particle4 = new ParticleSystem("TextData/Particles/potion_04.fx");
	//particle2->SetScale();
	//particle3->SetScale();		
	
}

HupgiFire::~HupgiFire()
{
	delete sprite;
	//delete particle3;
	//delete particle4;
}

void HupgiFire::Update()
{
	sprite->Update();
}

void HupgiFire::Render()
{
	sprite->Render();
}

void HupgiFire::GUIRender()
{

}

void HupgiFire::Play(Vector3 pos, Vector3 rot)
{
	sprite->PlayLoop(pos);
}

void HupgiFire::Stop()
{
	sprite->Stop();
	
}

