#include "Framework.h"
#include "SpiritFlame.h"
SpiritFlame::SpiritFlame()
{
	sprite = new Sprite(L"Textures/Effect/SpiritFlame.png", 250, 250, 8, 4, true);
	
}

SpiritFlame::~SpiritFlame()
{
	delete sprite;
}

void SpiritFlame::Update()
{
	sprite->Update();
}

void SpiritFlame::Render()
{
	sprite->Render();
}

void SpiritFlame::GUIRender()
{

}

void SpiritFlame::Play(Vector3 pos, Vector3 rot)
{
	sprite->Play(pos);
}

void SpiritFlame::Stop()
{
	sprite->Stop();
	//particle3->Stop();
	//particle4->Stop();
}

void SpiritFlame::ParticleRotate()
{
}

void SpiritFlame::SetPos(Vector3 pos)
{
	sprite->SetPos(pos);
	//particle3->SetPos(pos);
	//particle4->SetPos(pos);
}

void SpiritFlame::SetVortex(Vector3 pos)
{

	//particle3->SetPos(pos);
	//particle4->SetPos(pos);


}

