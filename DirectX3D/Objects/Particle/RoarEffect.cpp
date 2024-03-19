#include "Framework.h"
#include "RoarEffect.h"

RoarEffect::RoarEffect()
{
	roar = new ParticleSystem("TextData/Particles/roar.fx");
}

RoarEffect::~RoarEffect()
{
}

void RoarEffect::Update()
{
	roar->Update();
}

void RoarEffect::Render()
{
	roar->Render();
}

void RoarEffect::GUIRender()
{
}

void RoarEffect::Play(Vector3 pos, Vector3 rot)
{
	roar->Play(pos, rot);
}

void RoarEffect::roarCloserCam(Vector3 pos, Vector3 targetpos, float speed)
{		
	roar->CloserCam(roar->GetPos(), targetpos, speed);
	roar->GetPos() = Lerp(roar->GetPos(), targetpos, speed);
}

void RoarEffect::Stop()
{
}
