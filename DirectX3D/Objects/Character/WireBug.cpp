#include "Framework.h"

WireBug::WireBug()
	: ModelAnimator("WireBug")
{
	ReadClip("IDLE");
	Pos().y += 130; // ¹åÁÙ¹ú·¹ À§Ä¡´Â ¿©±â¼­ Á¶Á¤ÇÏ¸é µÊ
	Pos().x += 300;
	bugParticle = new ParticleSystem("TextData/Particles/bug_get.fx");
	bugLightParticle = new ParticleSystem("TextData/Particles/wire_bug_light.fx");
	bugLightParticle2 = new ParticleSystem("TextData/Particles/wire_bug_light2.fx");
	bugParticle->SetScale(2);
	bugLightParticle->SetScale(0.4f);
	bugLightParticle->Play({ Pos().x,Pos().y + 10,Pos().z }, 0);
	//bugLightParticle2->Play({ Pos().x,Pos().y + 10,Pos().z }, 0);
	

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	FOR(2) rasterizerState[i] = new RasterizerState();

	blendState[1]->Additive();
	//blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	//depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

	rasterizerState[1]->CullMode(D3D11_CULL_NONE);

	UpdateWorld();

	wireBugPickUpUI = new Quad(L"Textures/UI/WireBugPickUpUI.png");
	wireBugPickUpUI->Scale() *= 1.5f;
}

WireBug::~WireBug()
{
	delete wireBugPickUpUI;
}

void WireBug::Update()
{
	SetAnimation();
	Respawn();
	if (isActive == false && isPlay == true)
	{
		bugParticle->Play(Pos(), 0);
		bugLightParticle->Stop();
		//bugLightParticle2->Stop();
		isPlay = false;
	}
	bugLightParticle->Update();
	bugParticle->Update();
	//bugLightParticle2->Update();
	UpdateUI();

	ModelAnimator::Update();
}

void WireBug::Render()
{
	
	blendState[1]->SetState();
	depthState[1]->SetState();
	rasterizerState[1]->SetState();


	//bugLightParticle2->Render();
	bugLightParticle->Render();
	bugParticle->Render();
	blendState[0]->SetState();
	depthState[0]->SetState();
	rasterizerState[0]->SetState();

	if(Active())
		ModelAnimator::Render();
}

void WireBug::GUIRender()
{
	Model::GUIRender();
}

void WireBug::PostRender()
{
	if (isWireBugPickUpUIActive)
		wireBugPickUpUI->Render();
}

void WireBug::Respawn()
{
	if (!Active())
		respawnDuration += DELTA;

	if (respawnDuration > respawnDurationLimit)
	{
		SetActive(true);
		bugLightParticle->Play({ Pos().x,Pos().y + 10,Pos().z }, 0);
		bugLightParticle2->Play({ Pos().x,Pos().y + 10,Pos().z }, 0);
		respawnDuration = 0.0f;
		isPlay = true;
	}
}

void WireBug::SetAnimation()
{
	SetState(IDLE);
}

void WireBug::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	PlayClip(state);
}

void WireBug::UpdateUI()
{
	UIPos = Pos() + Vector3::Up() * 60;

	if (!CAM->ContainPoint(UIPos))
	{
		isWireBugPickUpUIActive = false;
		return;
	}

	wireBugPickUpUI->Pos() = CAM->WorldToScreen(UIPos);
	
	wireBugPickUpUI->UpdateWorld();
}
