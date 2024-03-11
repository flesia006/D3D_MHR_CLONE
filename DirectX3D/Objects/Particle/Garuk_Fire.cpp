#include "Framework.h"
#include "Garuk_Fire.h"

Garuk_Fire::Garuk_Fire()
{
	smoke = new ParticleSystem("TextData/Particles/garuk_fire_01.fx");
	fire = new ParticleSystem("TextData/Particles/garuk_fire_02.fx");
}

Garuk_Fire::~Garuk_Fire()
{
	delete smoke;
	delete fire;
}

void Garuk_Fire::Update()
{
	smoke->Update();
	fire->Update();
}

void Garuk_Fire::Render()
{
	smoke->Render();
	fire->Render();
}

void Garuk_Fire::GUIRender()
{
	smoke->GUIRender();
}

void Garuk_Fire::Play(Vector3 pos, Vector3 rot)
{
	smoke->Play(pos, rot);
	fire->Play(pos, rot);
}

void Garuk_Fire::Stop()
{
	smoke->Stop();
	fire->Stop();
}

void Garuk_Fire::ParticleRotate()
{
	smoke->ParticleRotate();
	fire->ParticleRotate();
}

